#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    enum Tipo{
        USUARIO, ADMINISTRADOR
    };
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    int getTipo()const{return mTipo;}
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_registrarPushButton_clicked();

private:

    void compruebaAdmin();
    Ui::Dialog *ui;
    int mTipo;
};
#endif // DIALOG_H
