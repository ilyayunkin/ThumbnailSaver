#include "mainwindow.h"

#include <QPushButton>
#include <QFileDialog>

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
            auto thumbnail = ThumbnailProvider::GetThumbnail(path);
            if(!thumbnail.isNull()){
                QString path = QFileDialog::getSaveFileName(this, tr("Choose file name for output PNG"));
                if(!path.isEmpty())
                {
                    QFile file(path);
                    if(file.open(QIODevice::WriteOnly)){
                        thumbnail.save(&file, "PNG");
                        file.close();
                    }
                }
            }
        }
    };
    connect(b, &QPushButton::clicked, f);
}
