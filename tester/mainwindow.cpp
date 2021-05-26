#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->insertColumn(0);
    ui->tableWidget->insertColumn(1);
    ui->tableWidget->insertColumn(2);
    ui->tableWidget->insertColumn(3);
    ui->tableWidget->insertColumn(4);
    ui->tableWidget->insertColumn(5);
    ui->tableWidget->insertColumn(6);
    ui->tableWidget->insertColumn(7);
    ui->tableWidget->insertColumn(8);
    ui->tableWidget->insertColumn(9);
    ui->tableWidget->insertColumn(10);
    ui->tableWidget->setColumnWidth(0, 500);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setColumnWidth(4, 100);
    ui->tableWidget->setColumnWidth(5, 500);
    ui->tableWidget->setColumnWidth(6, 500);
    ui->tableWidget->setColumnWidth(7, 500);
    ui->tableWidget->setColumnWidth(8, 500);
    ui->tableWidget->setColumnWidth(9, 500);
    ui->tableWidget->setColumnWidth(10, 500);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("URL"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Resp. Time, ms."));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Size"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Encoding"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("HTTP Code"));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Redirect Target"));
    ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("<title>"));
    ui->tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("<h1>"));
    ui->tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem("meta description"));
    ui->tableWidget->setHorizontalHeaderItem(9, new QTableWidgetItem("meta keywords"));
    ui->tableWidget->setHorizontalHeaderItem(10, new QTableWidgetItem("rel canonical"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QString content="HTTP Code Tester v0.46a\nCopyright (c) 2020 by Ighor Poteryakhin\nighor@ighor.ru\n";
    content+=QString("Compiled with QT ")+QT_VERSION_STR+QString(", rinning on ")+QSysInfo::productType()+" "+QSysInfo::productVersion()+"/"+QSysInfo::currentCpuArchitecture();
//    content+=QSysInfo::prettyProductName()+"/";

    QMessageBox::information(this, tr("About box") , tr(content.toLocal8Bit().data()));
}


void MainWindow::on_pauseButton_clicked()
{
    pause=!pause;
    ui->statusbar->showMessage("Paused",3000);

}

void MainWindow::on_stopButton_clicked()
{
    stop=true;
    ui->statusbar->showMessage("Stopped",3000);
}

void MainWindow::on_actionSave_To_File_triggered()
{
    mutex.lock();
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save To File"),"",tr("All Files (*);;Text Files (*.txt)"));
    if (fileName.length()!=0)
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::critical(0,qApp->tr("Ошибка!"),
            qApp->tr("\nНевозможно создать файл.")+
            qApp->tr("\nНажмите Cancel"), QMessageBox::Cancel);
        }
        else
        {
            QTextStream out(&file);
            out<<"URL\tResp. Time, ms.\tSize\tEncoding\tHTTP Code\tRedirect Target\t<title>\t<h1>\tmeta description\tmeta keywords\tcanonical\n";
            for(int i=0;i<ui->tableWidget->rowCount();i++)
            {
                if(ui->tableWidget->item(i,0)) // QTableWidgetItem
                    out<<ui->tableWidget->item(i,0)->text();
                for(int j=1;j<=ui->tableWidget->columnCount();j++)
                    if(ui->tableWidget->item(i,j)) // QTableWidgetItem
                        out<<"\t"<<ui->tableWidget->item(i,j)->text();
                    else
                        out<<QString("\t");
                out<<endl;
            }
        }
    }
    ui->statusbar->showMessage("Saved to file "+fileName,3000);
    mutex.unlock();
}


void MainWindow::on_actionCopy_To_Clipboard_triggered()
{
    mutex.lock();
    QString text,html;

    text+="URL\tResp. Time, ms.\tSize\tEncoding\tHTTP Code\tRedirect Target\t<title>\t<h1>\tmeta description\tmeta keywords\tcanonical\n";
    html+="<html><style>br{mso-data-placement:same-cell;}</style>\
           <table><tr><td><b>URL</b></td><td><b>Resp. Time, ms.</b></td><td><b>Size</b></td><td><b>Encoding</b></td><td><b>HTTP Code</b></td><td><b>Redirect Target</b></td><td><b>&lt;title&gt;</b></td><td><b>&lt;h1&gt;</b></td><td><b>meta description</b></td><td><b>meta keywords</b></td><td><b>canonical</b></td></tr>";

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
         html+="<tr>";
         if(ui->tableWidget->item(i,0))
         {
               text+=ui->tableWidget->item(i,0)->text();
               html+="<td  style=\"color: #"+ui->tableWidget->item(i,0)->foreground().color().name()+"\">"+ui->tableWidget->item(i,0)->text().toHtmlEscaped()+"</td>";
         }

         for(int j=1;j<=ui->tableWidget->columnCount();j++)
               if(ui->tableWidget->item(i,j))
               {
                           text+=QString("\t")+ui->tableWidget->item(i,j)->text();
                           QString bstart, bend;
                           if(ui->tableWidget->item(i,j)->foreground().color().name()!="#000000")
                           {
                               bstart="<b>"; bend="</b>";
                           }
                           html+="<td style=\"color:"+ui->tableWidget->item(i,j)->foreground().color().name()+";\">"+bstart+ui->tableWidget->item(i,j)->text().toHtmlEscaped()+bend+"</td>";
               }
               else
               {
                    text+=QString("\t");
                    html+="<td></td>";
               }

         html+="</tr>";
         text+="\n";
    }
    html+="</table>";

    QClipboard *clipboard = QApplication::clipboard();
    QMimeData * md = new QMimeData;
    md->setHtml(html);
    md->setText(text);
    //    clipboard->setText(text);
    clipboard->setMimeData(md);
    ui->statusbar->showMessage("Saved to clipboard",3000);
    mutex.unlock();
}

void MainWindow::on_actionLoad_From_Clipboard_triggered()
{
   mutex.lock();
   QClipboard *clipboard = QApplication::clipboard();
   QRegExp rx("\n");
   unsigned long count=0;

   QStringList query = clipboard->text().split(rx);
   for( auto q : query )
   {
//       qDebug() << q;
       if(q.trimmed()!=QString(""))
       {
            count++;
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(q.trimmed());
            ui->tableWidget->setItem(row, 0, item);
            ui->tableWidget->setRowHeight(row,24);
       }
   }
   ui->statusbar->showMessage("Loaded from clipboard, "+QString::number(count)+" url(s)",3000);
   mutex.unlock();
}

void MainWindow::on_actionLoad_From_File_triggered()
{
/*
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load From File"),"",tr("All Files (*);;Text Files (*.txt)"));
    unsigned long count=0;
    try
    {
        std::ifstream infile(fileName.toLocal8Bit().data());
        std::string s;
        for(infile >> s; !infile.eof(); infile >> s)
        {
            QString d=QString(s.c_str()).trimmed();
            if(d.trimmed()!=QString(""))
            {
                 count++;
                 int row = ui->tableWidget->rowCount();
                 ui->tableWidget->insertRow(row);
                 QTableWidgetItem *item = new QTableWidgetItem(d);
                 ui->tableWidget->setItem(row, 0, item);
            }
        }
    }
    catch(std::ios_base::failure &var)
    {
            QMessageBox::critical(this, "Error!", tr((char*)var.what()), QMessageBox::Abort);
    }
    ui->statusbar->showMessage("Loaded from file "+fileName+", "+QString::number(count)+" url(s)",3000);
*/

    mutex.lock();
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load From File"),"",tr("All Files (*);;Text Files (*.txt)"));
    unsigned long count=0;
    if (fileName.length()!=0)
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::critical(nullptr,qApp->tr("Ошибка!"),
            qApp->tr("\nНевозможно считать данные из файла.")+
            qApp->tr("\nНажмите Cancel"), QMessageBox::Cancel);
        }
        else
        {
            QTextStream in(&file);
            QString d;
            while (!in.atEnd())
            {
                if((d=in.readLine().toLocal8Bit().trimmed())!=QString(""))
                {
                     count++;
                     int row = ui->tableWidget->rowCount();
                     ui->tableWidget->insertRow(row);
                     QTableWidgetItem *item = new QTableWidgetItem(d);
                     ui->tableWidget->setItem(row, 0, item);
                }
            }
        }
    }
    ui->statusbar->showMessage("Loaded from file "+fileName+", "+QString::number(count)+" url(s)",3000);
    mutex.unlock();
}

unsigned MainWindow::Load(QDomDocument& doc)
{
    QDomElement docElem = doc.documentElement();

    unsigned long count=0;

/*
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    QTableWidgetItem *item = new QTableWidgetItem(.........);
    ui->tableWidget->setItem(row, 0, item);
*/

    QDomElement root = doc.documentElement();
    if (root.tagName() != "urlset")
    {
      qWarning("The file is not a bookindex file");
      qDebug()<<("The file is not a bookindex file");
      return 0;
    }

    QDomNode node = root.firstChild();
    while (!node.isNull())
    {
      if (node.toElement().tagName() == "url")
      {
         QDomNode uri = node.firstChild();
         while (!uri.isNull())
         {
//                     qDebug()<<uri.toElement().tagName();
             if (uri.toElement().tagName() == "loc")
             {
//                        qDebug()<<uri.toElement().text();
                count++;
                int row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row);
                QTableWidgetItem *item = new QTableWidgetItem(uri.toElement().text());
                ui->tableWidget->setItem(row, 0, item);
             }
             uri = uri.nextSibling();
         }

      }
      node = node.nextSibling();
    }
    return count;
}

void MainWindow::on_actionLoad_from_X_ML_triggered()
{
    unsigned count=0;
    mutex.lock();
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load From File"),"","XML Files (*.xml)");
    qDebug()<<fileName;
    if (fileName.length()!=0)
    {
        QFile file(fileName);
        QDomDocument doc;
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(nullptr,qApp->tr("Ошибка!"),
            qApp->tr("\nНевозможно открыть файл.")+
            qApp->tr("\nНажмите Cancel"), QMessageBox::Cancel);
        }
        else if (!doc.setContent(&file))
        {
            QMessageBox::critical(nullptr,qApp->tr("Ошибка!"),
            qApp->tr("\nНевозможно считать данные из файла.")+
            qApp->tr("\nНажмите Cancel"), QMessageBox::Cancel);
            file.close();
            return;
        }
        else
        {
            count=Load(doc);
            file.close();
        }
    }
    ui->statusbar->showMessage("Loaded from XML file "+fileName+", "+QString::number(count)+" url(s)",3000);
    mutex.unlock();

}

void MainWindow::on_actionLoad_from_Sitemap_URL_triggered()
{
    mutex.lock();
    bool ok;
    QString url = QInputDialog::getText(this, tr("URL"),
                                          tr("Sitemap URL:"), QLineEdit::Normal,
                                          "https://", &ok);
    mutex.unlock();
    if (!(ok && !url.isEmpty()))
        return;

    xmlmanager.get(QNetworkRequest((QUrl(url))));
    connect(&xmlmanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(gotXML(QNetworkReply*)));

}

void MainWindow::gotXML(QNetworkReply* reply)
{
    QByteArray body = reply->readAll();
    QList<QNetworkReply::RawHeaderPair> headers = reply->rawHeaderPairs();
    int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray httpStatusMessage = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toByteArray();

    unsigned count=0;
    if(httpStatus==200)
    {
        QDomDocument doc;
        doc.setContent(body);

        QDomElement root = doc.documentElement();
        if (root.tagName() == "urlset")
        {
              count=Load(doc);
              qDebug()<<"Loaded "<<reply->url().toDisplayString()<<count<<" pcs";
              mutex.lock();
              ui->statusbar->showMessage(QString("Loaded from remote sitemap ")+reply->url().toDisplayString()+" "+QString::number(count)+" url(s)",3000);
              mutex.unlock();
        }
        else
        if (root.tagName() == "sitemapindex")
        {
            qDebug()<<"sitemapindex";
            QDomNode node = root.firstChild();
            while (!node.isNull())
            {
              if (node.toElement().tagName() == "sitemap")
              {
                  qDebug()<<"Loading from: "<<node.toElement().elementsByTagName("loc").at(0).toElement().text();
                  mutex.lock();
                  ui->statusbar->showMessage("Loading from remote sitemap "+node.toElement().text(),3000);
                  mutex.unlock();
                  xmlmanager.get(QNetworkRequest((QUrl(node.toElement().elementsByTagName("loc").at(0).toElement().text()))));
                  connect(&xmlmanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(gotXML(QNetworkReply*)));
              }
              node = node.nextSibling();
            }
        }

    }
    else
    {
        mutex.lock();
        QMessageBox msgBox;
        msgBox.critical(this, "Error", "Requested URL is not accessible");
        mutex.unlock();
    }


}

void MainWindow::on_actionClea_r_All_triggered()
{
    mutex.lock();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->statusbar->showMessage("List cleared...",3000);
    mutex.unlock();
}

void MainWindow::on_actionE_xit_triggered()
{
    close();
}

Thread::Thread(QTableWidget *givenmodel, QMutex& givenmutex, int givenid, QObject *parent)
    : QThread(parent), model(givenmodel), mutex(givenmutex), id(givenid)
{
    thrcount++;
    timer.start();
}

Thread::~Thread()
{
    thrcount--;
}

int Thread::thrcount=0;

void Thread::run()
{
    mutex.lock();

    QUrl url(model->item(id,0)->text());

    mutex.unlock();

    QNetworkAccessManager manager;
    manager.get(QNetworkRequest(url));
    connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(httpRequestFinished(QNetworkReply*)));
//    connect(&manager,SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(httpRequestTimeout(QNetworkReply::NetworkError* )));
    qDebug()<<"Started "<<id<<" "<<url<<", threads "<<thrcount;
    this->exec();
}

void Thread::httpRequestFinished(QNetworkReply* reply)
{
    QUrl url(model->item(id,0)->text());
    QByteArray body = reply->readAll();
    QList<QNetworkReply::RawHeaderPair>  headers = reply->rawHeaderPairs();
    int httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray httpStatusMessage = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toByteArray();
    mutex.lock();
    QTableWidgetItem *item;
    if(timer.elapsed())
    {
       item = new QTableWidgetItem(QString::number(timer.elapsed()));
       model->setItem(id, 1, item);
    }
    if(body.size())
    {
        item = new QTableWidgetItem(QString::number(body.size()));
        model->setItem(id, 2, item);
    }
    if(httpStatus)
    {
        item = new QTableWidgetItem(QString::number(httpStatus));
        model->setItem(id, 4, item);
    }
    else
    {
        item = new QTableWidgetItem(QString("ERROR"));
        model->setItem(id, 4, item);
    }
    if(httpStatus>=300&&httpStatus<310)
    {
       item = new QTableWidgetItem(QString(reply->rawHeader("Location")));
       model->setItem(id, 5, item);
    }
    mutex.unlock();
    QString encoding=reply->header(QNetworkRequest::ContentTypeHeader).toString();
    if(encoding.startsWith("text/html"))
        encoding=encoding.section("charset=",-1,-1).toUpper();
    else
    {
        qDebug()<<"Done, body skipped "<<reply->url().toString()<<", threads "<<thrcount;
        quit();
        requestInterruption();
        wait();
        delete this;
        return;
    }

//    encoding=encoding.remove("text/html; charset=");
//    encoding=encoding.section("charset=",-1,-1).toUpper();
//    qDebug()<<encoding;
//    qDebug()<<body;

//        emit status("url: "+index0.data().toString(),idforstatus);
    mutex.lock();
    if(encoding!="")
    {
        item = new QTableWidgetItem(QString(encoding));
        model->setItem(id, 3, item);
    }
    if(httpStatus==200)
    {
        QTextCodec *codec = QTextCodec::codecForName(encoding.toLocal8Bit());
        auto doc = QGumboDocument::parse(codec->toUnicode(body));
        auto root = doc.rootNode();
/*
        auto nodes = root.getElementsByTagName(HtmlTag::TITLE);
        Q_ASSERT(nodes.size() == 1);

        auto title = nodes.front();
//    qDebug() << "title is: " << title.innerText();
        if(title.innerText()!=QString(""))
        {
            item = new QTableWidgetItem(QString(title.innerText().trimmed()));
            model->setItem(id, 4, item);
        }
*/
        unsigned titlecount=0;
        auto nodes = root.getElementsByTagName(HtmlTag::TITLE);
        for (const auto& node: nodes)
        {
//        qDebug() << "title: " << node.innerText();
            item = new QTableWidgetItem(QString(node.innerText().simplified()));
            item->setForeground(QBrush(QColor(0, 0, 0)));

            bool exists=false;
            for(const auto& found:model->findItems(QString(node.innerText().simplified()), Qt::MatchExactly))
                if(found->column()==6)
                    {
                        found->setForeground(QBrush(QColor(0, 0, 255)));
                        exists=true;
                    }
            if(exists)
                item->setForeground(QBrush(QColor(0, 0, 255)));

            model->setItem(id, 6, item);
            titlecount++;
        }
        if(titlecount>1)
        {
            item = new QTableWidgetItem(QString("MORE THAN ONE!"));
            item->setForeground(QBrush(QColor(255, 0, 0)));
            model->setItem(id, 6, item);
        }

        unsigned h1count=0;
        nodes = root.getElementsByTagName(HtmlTag::H1);

        for (const auto& node: nodes)
        {
//        qDebug() << "h1: " << node.innerText();
            if(node.childElementCount())
            {
//                qDebug()<<"Complex h1";
                for (const auto& child: node.childNodes())
                {
                    item = new QTableWidgetItem(QString(child.innerText().simplified()));
                    item->setForeground(QBrush(QColor(0, 0, 0)));

                    bool exists=false;
                    for(const auto& found:model->findItems(QString(node.innerText().simplified()), Qt::MatchExactly))
                        if(found->column()==7)
                            {
                                found->setForeground(QBrush(QColor(0, 0, 255)));
                                exists=true;
                            }
                    if(exists)
                        item->setForeground(QBrush(QColor(0, 0, 255)));

                    model->setItem(id, 7, item);
                    h1count++;
                }
            }
            else
            {
                item = new QTableWidgetItem(QString(node.innerText().simplified()));
                item->setForeground(QBrush(QColor(0, 0, 0)));

                bool exists=false;
                for(const auto& found:model->findItems(QString(node.innerText().simplified()), Qt::MatchExactly))
                    if(found->column()==7)
                        {
                            found->setForeground(QBrush(QColor(0, 0, 255)));
                            exists=true;
                        }
                if(exists)
                    item->setForeground(QBrush(QColor(0, 0, 255)));

                model->setItem(id, 7, item);
                h1count++;
            }
        }
        if(h1count>1)
        {
            item = new QTableWidgetItem(QString("MORE THAN ONE!"));
            item->setForeground(QBrush(QColor(255, 0, 0)));
            model->setItem(id, 7, item);
        }

        nodes = root.getElementsByTagName(HtmlTag::META);
        for (const auto& node: nodes)
        {
//            qDebug() << "META: " << node.getAttribute("name");
            if(node.getAttribute("name").toLower()==QString("description"))
            {
                item = new QTableWidgetItem(QString(node.getAttribute("content")).simplified());
                item->setForeground(QBrush(QColor(0, 0, 0)));

                bool exists=false;
                for(const auto& found:model->findItems( QString(node.getAttribute("content")).simplified(), Qt::MatchExactly))
                    if(found->column()==8)
                        {
                            found->setForeground(QBrush(QColor(0, 0, 255)));
                            exists=true;
                        }
                if(exists)
                    item->setForeground(QBrush(QColor(0, 0, 255)));

                model->setItem(id, 8, item);
            }
            if(node.getAttribute("name").toLower()==QString("keywords"))
            {
                item = new QTableWidgetItem(QString(node.getAttribute("content")).simplified());
                model->setItem(id, 9, item);
            }
        }
        nodes = root.getElementsByTagName(HtmlTag::LINK);
        for (const auto& node: nodes)
        {
            if(node.getAttribute("rel").toLower()==QString("canonical"))
            {
                item = new QTableWidgetItem(QString(node.getAttribute("href")).simplified());
                model->setItem(id, 10, item);
            }

        }

    }
    mutex.unlock();

    quit();
    requestInterruption();
    wait();
    qDebug()<<"Done "<<id<<" "<<url<<", threads "<<thrcount;
    delete this;
}

//void Thread::httpRequestError(QNetworkReply::NetworkError result)
//{
//}

void MainWindow::updateurl(const int i)
{
    Thread* httpthread=new Thread(ui->tableWidget,mutex,i,this);

//    connect(httpthread,SIGNAL(status(QString,int)),this,SLOT(status(QString,int)));

    while((httpthread->thrcount)>=HTTP_MAX_THREADS)
        qApp->processEvents();

    httpthread->start();
}

void MainWindow::on_startButton_clicked()
{
    stop=pause=false;
    mutex.lock();
    if(ui->tableWidget->rowCount()==0)
    {
        ui->statusbar->showMessage("Nothing to do",5000);
        mutex.unlock();
        return;
    }
    QWinTaskbarButton *button = new QWinTaskbarButton(this);
    button->setWindow(this->windowHandle());
    QWinTaskbarProgress *progress;
//    if(QSysInfo::productType()=="windows"&&QSysInfo::productVersion()>=7)
//    {
        progress = button->progress();
        progress->setVisible(true);
        progress->setMinimum(0);
        progress->setMaximum(ui->tableWidget->rowCount());
//    }
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(ui->tableWidget->rowCount());
    //!!!!!!!!!!!!!!!!!!!!!!!!
    mutex.unlock();

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        mutex.lock();
        ui->progressBar->setValue(i);
        progress->setValue(i);
        ui->statusbar->showMessage(ui->tableWidget->item(i,0)->text(),3000);
        mutex.unlock();
        if(stop)
            return;
        while(pause)
            qApp->processEvents();
        updateurl(i);
    }
    mutex.lock();
    ui->progressBar->setValue(ui->tableWidget->rowCount());
    progress->setValue(ui->tableWidget->rowCount());
    ui->statusbar->showMessage("All requests sent...",5000);
    delete button;
    mutex.unlock();

}

int MainWindow::addItems(QStringList list)
{
    unsigned count=0;
    for( auto q : list )
    {
        count++;
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        QTableWidgetItem *item = new QTableWidgetItem(q);
        ui->tableWidget->setItem(row, 0, item);
    }
    if(count)
        ui->statusbar->showMessage("Added from grabber "+QString::number(count)+" url(s)",3000);
    else
        ui->statusbar->showMessage("Cancelled",3000);

    return count;
}

void MainWindow::on_action_Grab_from_site_triggered()
{
    Grabber grabber;
    grabber.setModal(true);
    grabber.exec();
    addItems(grabber.result);
}
