#include "Aides.h"
#include <QSqlQuery>
#include <QtDebug>


#include "QString"
#include<QObject>
#include<QPdfWriter>
#include<QTextDocument>
#include<QDesktopServices>
#include <QSystemTrayIcon>

#include<QFileDialog>


int Aides::get_NUM_AIDE() {return NUM_AIDE;}
QString Aides::get_TYPE() {return TYPE;}
int Aides::get_QUANTITE() {return QUANTITE;}
QString Aides::get_DATE_ARRIVE() {return DATE_ARRIVE;}
QString Aides::get_VALIDITE_DU_AIDE() {return VALIDITE_DU_AIDE;}



void Aides::set_NUM_AIDE(int n) {this->NUM_AIDE=n;}
void Aides::set_TYPE(QString n) {TYPE=n;}
void Aides::set_QUANTITE(int n) {this->QUANTITE=n;}
void Aides::set_DATE_ARRIVE(QString n) {DATE_ARRIVE=n;}
void Aides::set_VALIDITE_DU_AIDE(QString n) {VALIDITE_DU_AIDE=n;}



Aides::Aides()
{
    NUM_AIDE=0;
    QUANTITE=0;
    TYPE="";
    DATE_ARRIVE="";
    VALIDITE_DU_AIDE="";
}
Aides::Aides(int NUM_AIDE,QString TYPE,int QUANTITE,QString DATE_ARRIVE,QString VALIDITE_DU_AIDE)
{
    this->NUM_AIDE=NUM_AIDE;
    this->TYPE=TYPE;
    this->QUANTITE=QUANTITE;
    this->DATE_ARRIVE=DATE_ARRIVE;
    this->VALIDITE_DU_AIDE=VALIDITE_DU_AIDE;

}
/********************************************ajouter*****************************************************************/
bool Aides::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(NUM_AIDE);
    QString res1=QString::number(QUANTITE);
    query.prepare("INSERT INTO Aide(NUM_AIDE,TYPE,QUANTITE,DATE_ARRIVE,VALIDITE_DU_AIDE)"
                  "VALUES (:NUM_AIDE,:TYPE,:QUANTITE, :DATE_ARRIVE,:VALIDITE_DU_AIDE)");

                        query.bindValue(":NUM_AIDE",res );
                        query.bindValue(":TYPE", TYPE );
                        query.bindValue(":QUANTITE",res1);
                        query.bindValue(":DATE_ARRIVE", DATE_ARRIVE);
                        query.bindValue(":VALIDITE_DU_AIDE", VALIDITE_DU_AIDE);

    return query.exec();
}
/********************************************afficher*****************************************************************/
QSqlQueryModel * Aides::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from Aide");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_AIDES"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("QUANTITE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_ARRIVE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("VALIDITE_DU_AIDE"));
    return model;
}




/********************************************supprimer*****************************************************************/
bool Aides::supprimer(int NUM_AIDE)
{
QSqlQuery query;
QString res=QString::number(NUM_AIDE);
query.prepare("Delete from Aide where NUM_AIDE= :NUM_AIDE");
query.bindValue(":NUM_AIDE",res);
return query.exec();
}



/********************************************modifier*****************************************************************/

bool Aides::modifier(int NUM_AIDE, QString TYPE, int QUANTITE, QString DATE_ARRIVE, QString VALIDITE_DU_AIDE)
{
    QSqlQuery query;
    query.prepare("UPDATE AIDE SET TYPE = :type, QUANTITE = :quantite, DATE_ARRIVE = :date_arrive, VALIDITE_DU_AIDE = :validite_du_aide WHERE NUM_AIDE = :num_aide");
    query.bindValue(":num_aide", NUM_AIDE);
    query.bindValue(":type", TYPE);
    query.bindValue(":quantite", QUANTITE);
    query.bindValue(":date_arrive", DATE_ARRIVE);
    query.bindValue(":validite_du_aide", VALIDITE_DU_AIDE);
    if(query.exec())
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*
bool Aides::modifier(int NUM_AIDE, QString TYPE, int QUANTITE, QString DATE_ARRIVE, QString VALIDITE_DU_AIDE)
{
    QSqlQuery query;
    QString res1=QString::number(NUM_AIDE);
    query.prepare("update évènements set TYPE='"+TYPE+"', QUANTITE='"+QUANTITE+"', DATE_ARRIVE='"+DATE_ARRIVE+"',VALIDITE_DU_AIDE= '"+VALIDITE_DU_AIDE+"' where NUM_AIDE='"+NUM_AIDE+"'");
    return query.exec();
}
*/


/********************************************pdf*****************************************************************/
void Aides::pdf()
{
    QSqlQuery query;
     query.exec("SELECT NUM_AIDE, TYPE, QUANTITE, DATE_ARRIVE, VALIDITE_DU_AIDE, FROM AIDES");
     QPdfWriter writer("C:/Users/ahmed/OneDrive/Desktop/interface/123.pdf");
     QTextDocument document;
     writer.setTitle("Liste des Aides");
     QString title = "<h1>Liste des Aides</h1>";
     QString table = "<table border='1'><tr><th>Numero Aides</th><th>Type Aides</th><th>Quantite</th><th>Date d'arrive</th><th>Validiter du Aides</th></tr>";
     while (query.next()) {
         int Numero = query.value(0).toInt();
         QString Nom = query.value(1).toString();
         QString Date_evenement = query.value(2).toString();
         QString Lieu = query.value(3).toString();
         int nombre_des_participants = query.value(4).toInt();
         QString Actions = query.value(4).toString();
         table += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td></tr>").arg(Numero).arg(Nom).arg(Date_evenement).arg(Lieu).arg(nombre_des_participants).arg(Actions);
     }
     table += "</table>";
     document.setHtml(title + table);
     document.print(&writer);
     QString file_path = "C:/Users/ahmed/OneDrive/Desktop/interface/123.pdf";
     QDesktopServices::openUrl(QUrl::fromLocalFile(file_path));

}



/********************************************Trie****************************************************************/
QSqlQueryModel *Aides::trie()
{
    QSqlQueryModel * model=new QSqlQueryModel();


 model->setQuery("select * from Aide ORDER BY  NUM_AIDE  ASC ");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_AIDE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("QUANTITE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_ARRIVE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("VALIDITE_DU_AIDE"));

    return  model;
}


/********************************************rechercher*****************************************************************/
QSqlQueryModel * Aides::search(QString type)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM Aide WHERE TYPE LIKE '"+type+"%' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM_AIDE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("QUANTITE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_ARRIVE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("VALIDITE_DU_AIDE"));
    return model;
}



/********************************************ajout image*****************************************************************/
void Aides::ajout_image(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Impossible d'ouvrir le fichier" << filename;
        return;
    }
    QByteArray image = file.readAll();
    file.close();

    QSqlQuery query;
    query.prepare("UPDATE Aide SET image = :image WHERE NUM_AIDE = :NUM_AIDE");
    query.bindValue(":image", image);
    query.bindValue(":NUM_AIDE", NUM_AIDE);

    if(!query.exec())
    {
        qDebug() << "Erreur lors de l'ajout de l'image :" ; // << query.lastError().text();
    }
    else
    {
        qDebug() << "Image ajoutée avec succès";
    }
}



/********************************************notification*****************************************************************/
/*
void Aides::checkStockValidity() {
    QString validite = get_VALIDITE_DU_AIDE();
    // vérifiez si la validité est expirée
    if (validite < Qdate::currentDate()) {
        emit stockExpired();
    }
}


void Aides::checkStockValidity()
{
    QSqlQuery query;
    query.exec("SELECT NUM_AIDE, VALIDITE_DU_AIDE FROM Aides WHERE QUANTITE > 0");
    while (query.next()) {
        int num_aide = query.value(0).toInt();
        QString validite_du_aide = query.value(1).toString();
        QDate validite = QDate::fromString(validite_du_aide, "yyyy-MM-dd");
        if (validite < QDate::currentDate()) {
            QSqlQuery queryUpdate;
            queryUpdate.prepare("UPDATE Aides SET QUANTITE = 0 WHERE NUM_AIDE=:num_aide");
            queryUpdate.bindValue(":num_aide", num_aide);
            queryUpdate.exec();
        }
    }
}
*/
void Aides::notification_dajout_aide()
{
    // Créer une icône de la barre d'état système pour afficher la notification
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon();

    // Charger l'icône à afficher dans la notification
    QIcon icon(":/icons/notification_icon.png");

    // Configurer l'icône de la barre d'état système
    trayIcon->setIcon(icon);
    trayIcon->setVisible(true);

    // Afficher la notification avec un message personnalisé
    trayIcon->showMessage("Nouvel aide ajouté","Un nouvel aide a été ajouté à la base de données.",QSystemTrayIcon::Information,5000); // Afficher la notification pendant 5 secondes
}




