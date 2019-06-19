#include "mainwindow.h"

#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include "ThumbnailProvider.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QPushButton *b = new QPushButton("Get thumbnail for file");
    setCentralWidget(b);
    auto f = [&](bool triggered)
    {
        Q_UNUSED(triggered);
        QString path = QFileDialog::getOpenFileName(this, tr("Choose original file"));
        if(!path.isNull())
        {
            bool ok = false;

            auto thumbnail = ThumbnailProvider::GetThumbnail(path);
            if(!thumbnail.isNull()){
                QString path = QFileDialog::getSaveFileName(this, tr("Choose file name for output PNG"));
                if(!path.isEmpty())
                {
                    QFile file(path);
                    if(file.open(QIODevice::WriteOnly)){
                        thumbnail.save(&file, "PNG");
                        file.close();
                        ok = true;
                    }
                }
            }

            if(!ok){
                QMessageBox::critical(this, "Error", "Can't to save thumbnail");
            }else{
                QMessageBox::information(this, "Saved", "Thumbnail is saved");
            }
        }
    };
    connect(b, &QPushButton::clicked, f);
}
