#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

#include <QString>
#include <QSizePolicy>
#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
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
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().constFirst()))
    {}
}

void MainWindow::initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog)
    {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
                                              ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    for (const QByteArray &mimeTypeName : supportedMimeTypes)
    {
        mimeTypeFilters.append(mimeTypeName);
    }
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    dialog.setAcceptMode(acceptMode);
    if (acceptMode == QFileDialog::AcceptSave)
    {
        dialog.setDefaultSuffix("jpg");
    }
}

bool MainWindow::loadFile(const QString &fileName)
{
    std::cout << fileName.toStdString() << std::endl;
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull())
    {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                         .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }
    else
    {
        std::cout << "Loaded image \n";
    }
    return true;
}



