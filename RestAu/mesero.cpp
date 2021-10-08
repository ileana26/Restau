#include "mesero.h"
#include "ui_mesero.h"
#include "iniciosesion.h"
#include "QStandardItemModel"
#include "QPrintDialog"
#include <QPrinter>
#include <string>
#include "string"
#include "QPrintDialog"
#include <QPdfWriter>
#include <QTextDocument>
#include <QDesktopServices>
#include <QPainter>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QTabWidget>

mesero::mesero(int Id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mesero)
{
    IdMesero = QString::number(Id);
    ui->setupUi(this);

    ui->total->setDisabled(true);

    //BUSQUEDA DE PLATILLOS PARA EL MESERO Y VERIFICAR SU DISPONIBILIDAD

    QStringList elementos;

    ui->TablaPlatillos->setColumnCount(5);
    elementos << "ID Platillo" << "Nombre" << "Descripcion " << "Raciones" << "Costo" << "Tipo";
    ui->TablaPlatillos->setHorizontalHeaderLabels(elementos);

    QSqlQuery Platillos;
    Platillos.prepare("select idComida,nombre,descripcion,raciones,costo,tipo from comida");
    Platillos.exec();

    while(Platillos.next()){

        QString idplatillo = Platillos.value(0).toString();
        QString nombre = Platillos.value(1).toString();
        QString descripcion = Platillos.value(2).toString();
        QString raciones = Platillos.value(3).toString();
        QString costo = Platillos.value(4).toString();
        QString tipo = Platillos.value(5).toString();

        ui->TablaPlatillos->insertRow(ui->TablaPlatillos->rowCount());

        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,0,new QTableWidgetItem(idplatillo));
        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,1,new QTableWidgetItem(nombre));
        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,2,new QTableWidgetItem(descripcion));
        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,3,new QTableWidgetItem(raciones));
        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,4,new QTableWidgetItem(costo));
        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,5,new QTableWidgetItem(tipo));

    }

    //Creacion del drag and drop para la inicializacion del pedido
    QSqlQuery comida;

    //primera lista con el menu que se va a desplegar (desayunos)
    ui->listamenu->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listamenu->setDragEnabled(true);
    ui->listamenu->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listamenu->viewport()->setAcceptDrops(false);
    ui->listamenu->setDropIndicatorShown(true);

    //primera lista con el menu que se va a desplegar (bebidas)
    ui->bebidas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->bebidas->setDragEnabled(true);
    ui->bebidas->setDragDropMode(QAbstractItemView::DragDrop);
    ui->bebidas->viewport()->setAcceptDrops(false);
    ui->bebidas->setDropIndicatorShown(true);

    //primera lista con el menu que se va a desplegar (postres)
    ui->postres->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->postres->setDragEnabled(true);
    ui->postres->setDragDropMode(QAbstractItemView::DragDrop);
    ui->postres->viewport()->setAcceptDrops(false);
    ui->postres->setDropIndicatorShown(true);


    //segunda lista con los elementos seleccionados

    ui->listapedido->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listapedido->setDragEnabled(true);
    ui->listapedido->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listapedido->viewport()->setAcceptDrops(true);
    ui->listapedido->setDropIndicatorShown(true);

    comida.prepare("select idComida,nombre,descripcion,raciones,costo,tipo from comida");
    comida.exec();


    //segmento los alimentos, el postre y la comida en varios qlistwidget para mejor usabilidad y los agrego a sus respectivas listas para el drag and drop
    while(comida.next()){
        QString idcomida = comida.value(0).toString();
        QString nom = comida.value(1).toString();
        QString des = comida.value(2).toString();
        QString rac = comida.value(3).toString();
        QString cos = comida.value(4).toString();
        QString tip = comida.value(5).toString();

        if(comida.value(5) == "Desayunos"){

            QString datos =idcomida+"\n"+"Nombre: " +nom + "\nCosto: " +cos;
            QListWidgetItem * menu = new QListWidgetItem;
            menu->setText(datos);
            ui->listamenu->addItem(datos);
        }

        if(comida.value(5) == "Bebidas"){

            QString bebidas = idcomida+"\n"+"Nombre: " +nom + "\nCosto: " +cos;
            QListWidgetItem * bebida = new QListWidgetItem;
            bebida->setText(bebidas);
            ui->bebidas->addItem(bebidas);
        }

        if(comida.value(5) == "Postres"){

            QString postres =idcomida+"\n"+"Nombre: " +nom + "\nCosto: " +cos;
            QListWidgetItem * postre = new QListWidgetItem;
            postre->setText(postres);
            ui->postres->addItem(postres);
        }
    }
}

mesero::~mesero()
{
    delete ui;
}

void mesero::on_Salir_clicked()
{
    close();
    InicioSesion * Volver = new InicioSesion();
    Volver->show();

}

void mesero::on_lineEdit_textChanged(const QString &arg1)
{

    //FUNCION PARA QUE SE BUSQUE EN TUEMPO REAL ESTE PEDO
    ui->TablaPlatillos->setColumnCount(0);
    ui->TablaPlatillos->setRowCount(0);

    QStringList elementos;

    ui->TablaPlatillos->setColumnCount(5);
    elementos << "ID Platillo" << "Nombre" << "Descripcion " << "Raciones" << "Costo" << "Tipo";
    ui->TablaPlatillos->setHorizontalHeaderLabels(elementos);

    QSqlQuery BuscaPlatillo;
    BuscaPlatillo.prepare("select idcomida,nombre,descripcion,raciones,costo,tipo from comida where idcomida like '%"+arg1+"%' ");
    BuscaPlatillo.exec();

    while(BuscaPlatillo.next()){

        QString idplatillo = BuscaPlatillo.value(0).toString();
        QString nombre = BuscaPlatillo.value(1).toString();
        QString descripcion = BuscaPlatillo.value(2).toString();
        QString raciones = BuscaPlatillo.value(3).toString();
        QString costo = BuscaPlatillo.value(4).toString();
        QString tipo = BuscaPlatillo.value(5).toString();

        ui->TablaPlatillos->insertRow(ui->TablaPlatillos->rowCount());

        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,0,new QTableWidgetItem(idplatillo));
        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,1,new QTableWidgetItem(nombre));
        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,2,new QTableWidgetItem(descripcion));
        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,3,new QTableWidgetItem(raciones));
        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,4,new QTableWidgetItem(costo));
        ui->TablaPlatillos->setItem(ui->TablaPlatillos->rowCount()-1,5,new QTableWidgetItem(tipo));
    }
}

void mesero::on_Buscar_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void mesero::on_NuevoPedido_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mesero::on_CrearPedido_clicked()
{
    QStringList compra;
    QString pedido;
    QString imp;
    QString montofinal;
    //la variable venta descompone el qstringlist en una sola cadena
    QString venta;
    QString Importe;
    QString ID;
    QString pre;
    QString mesaa;
    QMessageBox message1;

    QString id;

    importetotal= 0;
    int cont = ui->listapedido->count();

    QSqlQuery orden;


    //if para verificar que en la segunda qlist hayan elementos y trabajar sobre ellos generando un contador y usado en el for
    if(cont != 0){
        for(int i =0; i < cont; i++){
            QListWidgetItem * pedi = ui->listapedido->item(i);
            //la variable pedido almacena los datos de los platillos que se han seleccionado
            pedido = pedi->text();

            //uso la funcion right para obtener los precios del string pedido ya que se almacena como cadena, obtengo los ultimos caracteres que es el costo y de ahi mero
            imp = pedido.right(2);
            //lo convierto a int
            totalcomida = imp.toInt();
            //y lo sumo para obtener el importe total
            importetotal += totalcomida;

            ui->total->setValue(importetotal);

            //dentro de este qlist almaceno los datos del pedido para segmentarlos despues en el ticket
            compra << pedido;

            //------------ Agrega los platillos a la base de datos ------------------

            pre = QString::number(importetotal);
            qDebug()<<pre;

            QRegExp sep("\\s+");
            id=pedido.section(sep,0,0);
            idco=id.toInt();

            ID = QString::number(idco);
            qDebug()<<ID;
            //mesa
            mesaa=ui->mesa->text();
            qDebug()<<mesaa;

            orden.prepare("call InsertarOrden(10005,'"+pre+"','"+ID+"','"+mesaa+"')");
            orden.exec();


        }

        //convierto la variable del importe total a string para su impresion
        Importe = QString::number(importetotal);
        qDebug()<<Importe;




        //RECORDATORIO PARA MARTES, CONVERTIR EL QSTRINGLIST TO QSTRING

        //conversion QLIst to String
        //la funcion join une todos los elementos de un qstringlist a un solo string delimitado por lo que le pases, en este caso son espacios nomas
        venta = compra.join("        ");

        //mensaje de validacion dirias tu mi amor
        message1.setWindowTitle("Agregar Pedido");
        message1.setIcon(QMessageBox::Question);
        message1.setText("¿Esta seguro de que desea iniciar el siguiente pedido?");
        QAbstractButton * btnYes = message1.addButton(tr("Si"),QMessageBox::YesRole);
        QAbstractButton * btnNo = message1.addButton(tr("No"),QMessageBox::YesRole);
        message1.exec();

           if(message1.clickedButton() == btnYes){

                //CAMBIEN LA DIRECCION DONDE SE VA A GENERAR EL PDF
               QPdfWriter pdf("/Users/ilean/Desktop/Ticket.pdf");

               QPainter painter(&pdf);

               painter.setPen(Qt::black);
               painter.drawText(100,0,"Le Restau: Tripa Vacia, Corazon Sin Alegria. ");
               painter.drawText(100,400,"Avenida San Claudio, Blvrd 14 Sur, Cdad. Universitaria, 72592 Puebla, Pue.");
               painter.drawText(100,600,"Codigo Postal: 78653");
               painter.drawText(100,800,"Ticket de compra/venta.");
               painter.drawText(100,1000,"---------------------------------------------------------------------------");
               painter.drawText(100,1200, venta);
               painter.drawText(100,1400,"Importe: $" + Importe + "");
               painter.drawText(100,1600,"----------------------------------------------------------------------------");
               painter.drawText(100,1800,"Dudas y Aclaraciones al 2441263382 ");
               painter.drawText(100,2000,"Pago realizado con MASTERCARD **************4325 en una sola exhibicion. ");
               painter.drawText(100,2200,"Muchas gracias por su compra.");
               painter.drawText(100,2400,"14/Febrero/2021 19:45:13");
               painter.drawPixmap(QRect(100,2600,2000,300),QPixmap("://img/Iconos/codigobarras.jfif"));

               painter.drawText(100,3100,"¡Reviens Vite!");
               painter.end();

               QMessageBox::information(this,"Pedido","El pedido se ha realizado correctamente.","Aceptar");
           }
        }
    else{
        QMessageBox::warning(this,"Error","No se ha podido crear el ticket de compra. ","Aceptar");
    }



}



void mesero::on_listapedido_itemSelectionChanged()
{
    ui->listapedido->setAcceptDrops(false);
}

void mesero::on_NuevoPedido_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    QStringList elementos;

    ui->tableWidget->setColumnCount(6);
    elementos << "Nombre" << "Apellido" << "Mesa" << "Platillo" << "idPlatillo" << "Entregado";
    ui->tableWidget->setHorizontalHeaderLabels(elementos);
    QSqlQuery ordenes;
    ordenes.prepare("select u.nombre,u.apellidoMaterno,m.idMesa,c.nombre,o.idComida,o.estatus  from usuario as u inner join mesero as me on u.idUsuario=me.idMesero inner join mesa as m on me.idMesero=m.mesero_idMesero inner join orden as o on m.idMesa=o.mesa_idMesa inner join comida as c on c.idComida=o.idComida where u.idUsuario='"+IdMesero+"' and o.estatus='Finalizada.'");
    qDebug()<<IdMesero;
    ordenes.exec();
    int i=0;
    while(ordenes.next())
    {

        QComboBox* myComboBox = new QComboBox(); // making a new dropdown box
        myComboBox->setObjectName(QString::number(i)); // pass column number as object name
        myComboBox->addItem("      ");
        myComboBox->addItem("Entregar");
        myComboBox->addItem("Cancelar");
        myComboBox->setStyleSheet("background-color:orange");

        QString nombre = ordenes.value(0).toString();
        QString Apellido = ordenes.value(1).toString();
        QString idMesa = ordenes.value(2).toString();
        QString Platillos = ordenes.value(3).toString();
        QString estatus = ordenes.value(4).toString();

        connect(myComboBox, SIGNAL(currentIndexChanged(QString)), SLOT(onComboChanged(QString)));

        ui->tableWidget->setCellWidget(0,i,myComboBox); // put box into table


        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(nombre));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(Apellido));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(idMesa));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(Platillos));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(estatus));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,5,myComboBox);
        i++;

    }


}

void mesero::onComboChanged(const QString & text)
   {
    qDebug() << text;
       QComboBox * comboBox = dynamic_cast<QComboBox *>(sender());
       int column = comboBox->objectName().toInt();  // retrieve column number
        QString idcita = ui->tableWidget->item(column,4)->text();


    QMessageBox message1;
    message1.setWindowTitle("Recibir Pedido");
    message1.setIcon(QMessageBox::Question);
    message1.setText("El pedido está listo,¿Confirmar entrega?");
    QAbstractButton * btnYes = message1.addButton(tr("Si"),QMessageBox::YesRole);
    QAbstractButton * btnNo = message1.addButton(tr("No"),QMessageBox::YesRole);
    message1.exec();


     if(message1.clickedButton() == btnYes && text =="Entregar")
     {
          comboBox->setStyleSheet("background-color:green");
         QMessageBox::information(this,"Pedido","El pedido se ha realizado correctamente.","Aceptar");

         QSqlQuery entregado;
         entregado.prepare("update orden set estatus = 'Entregado.' where idComida = "+idcita+"");
         entregado.exec();

     } else if(message1.clickedButton() == btnYes && text =="Cancelar")
     {
        comboBox->setStyleSheet("background-color:red");
         QMessageBox::warning(this,"Error","Platillo Cancelado","Aceptar");
        QSqlQuery eliminado;
        eliminado.prepare("delete from orden where idComida="+idcita+"");
        eliminado.exec();
     }
     else
     {
         QMessageBox::warning(this,"Error","Platillo sin cambios","Aceptar");
     }




   }
