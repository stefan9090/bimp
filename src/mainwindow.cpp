#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "Logger.h"
#include "Utils.h"

#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
#include <QSizePolicy>
#include <QStandardPaths>
#include <QString>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          m_pUi(new Ui::MainWindow),
                                          m_pImageLabel(new QLabel)
{
    m_pUi->setupUi(this);

    m_pImageLabel->setBackgroundRole(QPalette::Base);
    m_pImageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_pImageLabel->setScaledContents(true);

    setCentralWidget(m_pImageLabel);

    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
    delete m_pUi;
}

void MainWindow::createActions()
{
    pOpenAct = new QAction(tr("&Open"), this);
    pOpenAct->setStatusTip(tr("Open an image"));
    connect(pOpenAct, &QAction::triggered, this, &MainWindow::open);
}

void MainWindow::createMenus()
{
    pFileMenu = menuBar()->addMenu(tr("&File"));
    pFileMenu->addAction(pOpenAct);
}

void MainWindow::open()
{
    std::string strImageDir = Utils::getEnv("BIM_IMAGE_DIR", "/home/stefan/Pictures/test.png");

    QImage image = loadImage(strImageDir);

    image.for

    if (!image.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(image);
        m_pImageLabel->setPixmap(pixmap);
    }

}

QImage MainWindow::loadImage(const std::string &strFileName)
{
    QString strQFileName = QString::fromStdString(strFileName);

    QImageReader reader(strQFileName);
    reader.setAutoTransform(true);
    QImage newImage = reader.read();
    if (newImage.isNull())
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                         .arg(QDir::toNativeSeparators(strQFileName), reader.errorString()));
    }
    else
    {
        LOG_INFO("Loaded file: {}", strFileName);
    }

    return newImage;
}
