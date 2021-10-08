#ifndef MESERO_H
#define MESERO_H

#include <QWidget>
#include <QString>
#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <qdebug.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


namespace Ui {
class mesero;
}

class mesero : public QDialog
{
    Q_OBJECT

public:
    explicit mesero(int Id,QWidget *parent = nullptr);

    ~mesero();

private slots:


void onComboChanged(const QString & text);


    void on_Salir_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_Buscar_clicked();

    void on_NuevoPedido_clicked();

    void on_CrearPedido_clicked();

    void on_listapedido_itemSelectionChanged();

    void on_NuevoPedido_2_clicked();

private:
    Ui::mesero *ui;
    QSqlDatabase  conexion;
    QString IdMesero;
    int importe,totalcomida,importetotal,idco;


};

#endif // MESERO_H
