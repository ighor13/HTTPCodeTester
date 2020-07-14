#include "grabber.h"
#include "ui_grabber.h"

Grabber::Grabber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grabber)
{
    ui->setupUi(this);
}

Grabber::~Grabber()
{
    delete ui;
}

void Grabber::updateurl(const QUrl url)
{
    GThread* httpthread=new GThread(ui->listWidget,mutex,url,this);
    while((httpthread->thrcount)>=HTTP_MAX_THREADS)
        qApp->processEvents();
    httpthread->start();
}

void Grabber::on_scanButton_clicked()
{
    mutex.lock();
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(1);
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    mutex.unlock();

    startfrom=ui->lineEdit->text();
//    qDebug()<<startfrom.scheme();
//    qDebug()<<startfrom.host();

    mutex.lock();
    ui->listWidget->addItem(ui->lineEdit->text());
    mutex.unlock();

    bool finish;
    do
    {
        finish=true;
        do
        {
            int i=0,c;
            do
            {
                mutex.lock();
                c=ui->listWidget->count();
                ui->progressBar->setMaximum(c);
                if(!done[ui->listWidget->item(i)->text()])
                {
                    done[ui->listWidget->item(i)->text()]=true;
                    ui->progressBar->setValue(i);
                    mutex.unlock();
                    updateurl(ui->listWidget->item(i)->text());
                    qApp->processEvents();
                    finish=false;
                }
                else
                    mutex.unlock();
                qApp->processEvents();
            } while(++i<c);
            qApp->processEvents();
        } while(GThread::thrcount>0);
    } while(!finish);

    mutex.lock();
    ui->progressBar->setValue(ui->listWidget->count());
    mutex.unlock();
}

void Grabber::on_addButton_clicked()
{
    for(const auto& item: ui->listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard))
           result.push_back(item->text());

 /* // variant
    int c = ui->listWidget->count();
    for (int i = 0; i < c ; ++i)
    {
        QString s = QString::number(i);
        QModelIndex *model_index = new QModelIndex(ui->listWidget->model()->index(i,0) ); //0th column since we have one cloumn in listwidget
        QString q= model_index->data(Qt::DisplayRole).toString();
        result.push_back(q);
    }
*/
    this->close();
}

void Grabber::on_addSelectdButton_clicked()
{
    for(const auto& item: ui->listWidget->selectedItems())
        result.push_back(item->text());

    this->close();
}

void Grabber::on_cancelButton_clicked()
{
    this->close();
}

GThread::GThread(QListWidget *givenmodel, QMutex& givenmutex, const QUrl givenurl, QObject *parent)
    : QThread(parent), model(givenmodel), mutex(givenmutex), url(givenurl)
{
    thrcount++;
    state=none;
}

GThread::~GThread()
{
    thrcount--;
}

int GThread::thrcount=0;

void GThread::run()
{
    QNetworkAccessManager manager;
    QNetworkRequest request=QNetworkRequest(url);
//    request.setRawHeader("Accept", "text/html,text/plain;q=0.8,none;q=0.5");

    manager.head(request);
    connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(httpRequestFinished(QNetworkReply*)));
    qDebug()<<"Headed "<<url.toString()<<", threads "<<thrcount;
    while(state==none)
        qApp->processEvents(); // wait
    if(state==ready)
    {
        manager.get(request);
        qDebug()<<"Started "<<url.toString()<<", threads "<<thrcount;
    }
    else if(state==skip)
    {
        ;// code has no effect ?
    }

//    connect(&manager,SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(httpRequestTimeout(QNetworkReply::NetworkError* )));
    this->exec();

}


void GThread::httpRequestFinished(QNetworkReply* reply)
{
    QList<QNetworkReply::RawHeaderPair>  headers = reply->rawHeaderPairs();
    int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray httpStatusMessage = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toByteArray();
    QString encoding=reply->header(QNetworkRequest::ContentTypeHeader).toString();

    if(reply->operation()==QNetworkAccessManager::HeadOperation)
    {
        if(encoding.startsWith("text/html"))
        {
           // select in list
           mutex.lock();
           auto items=model->findItems(url.toString(),Qt::MatchExactly);
           if(!items.empty())
           for (const auto& item: items)
                item->setSelected(true);
           mutex.unlock();
           this->state=ready;
        }
        else
        {
           qDebug()<<"Skipped "<<url.toString()<<", threads "<<thrcount;
           this->state=skip;
           quit();
           requestInterruption();
           wait();
           delete this;
        }
    }
    else
    {
//    qDebug()<<reply->url()<<" "<<encoding;
        QByteArray body = reply->readAll();
        encoding=encoding.section("charset=",-1,-1).toUpper();
//    qDebug()<<reply->url();
//    qDebug()<<encoding;
//    qDebug()<<body;
//    qDebug()<<httpStatus;

        if(httpStatus==200)
        {
            QTextCodec *codec = QTextCodec::codecForName(encoding.toLocal8Bit());
            auto doc = QGumboDocument::parse(codec->toUnicode(body));
            auto root = doc.rootNode();
            // <base href="https://awakom.ru/">
            auto bases = root.getElementsByTagName(HtmlTag::BASE);
            QString basehref="";
            for (const auto& base: bases)
            {
                qDebug() << "BASE: " << base.getAttribute("href");
                basehref=QString(base.getAttribute("href").simplified());
            }

            auto nodes = root.getElementsByTagName(HtmlTag::A);
            for (const auto& node: nodes)
            {
                QUrl url=node.getAttribute("href").simplified();
                if (!(url.toString().indexOf("http://")==0||url.toString().indexOf("https://")==0||url.toString().indexOf("mailto:")==0||url.toString().indexOf("tel:")==0))
                    if(!(url.toString().indexOf("/")==0))
                        url=basehref+node.getAttribute("href").simplified();

                url=url.toString(QUrl::RemoveFragment);
                if(url.host()==QString(""))
                    url.setHost(reply->url().host());
                if(url.scheme()==QString(""))
                    url.setScheme(reply->url().scheme());
                if(url.path()==QString(""))
                    url.setPath("/");
                if(url.host().endsWith(reply->url().host()) || reply->url().host().endsWith(url.host()))
                {
                    mutex.lock();
                    if(model->findItems(url.toString(),Qt::MatchExactly).empty())
                    {
                        model->addItem(url.toString());
                        mutex.unlock();
                    }
                    else
                        mutex.unlock();
                }
            }
        }
        qDebug()<<"Done "<<url.toString()<<", threads "<<thrcount;
        quit();
        requestInterruption();
        wait();
        delete this;
    }
}
