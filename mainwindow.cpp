#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialog.h"
#include "controlusuariosform.h"
#include <QMessageBox>
#include <QMdiSubWindow>

MainWindow::MainWindow(int tipo, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
    if(tipo == Dialog::ADMINISTRADOR){
        ui->actionBase_de_datos_de_usuarios->setEnabled(true);
    }else{
        ui->actionBase_de_datos_de_usuarios->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBase_de_datos_de_usuarios_triggered()
{
    auto ctrlUsuarios = new ControlUsuariosForm(this);
    auto subWindow = ui->mdiArea->addSubWindow(ctrlUsuarios);
    subWindow->setGeometry(ctrlUsuarios->geometry());
    subWindow->setWindowTitle(ctrlUsuarios->windowTitle());
    subWindow->show();
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_actionAcerca_de_triggered()
{
    QMessageBox::aboutQt(this,"Qt");
}
