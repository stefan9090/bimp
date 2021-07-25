#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QFileDialog>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    QImage loadImage(const std::string &strFileName);

private:
    static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);
    void open();

    void createMenus();
    void createActions();

private:
    Ui::MainWindow *m_pUi;
    QImage m_image;
    QLabel *m_pImageLabel;

    QMenu *pFileMenu;
    QAction *pOpenAct;

};

#endif // MAINWINDOW_H