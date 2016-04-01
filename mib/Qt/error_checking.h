#ifndef HEADER_6B6D3C70B164F4A8
#define HEADER_6B6D3C70B164F4A8

#include <QMessageBox>

void is_sql_open(QSqlDatabase &db)
{
  if (!db.open())
    QMessageBox::information(0, "Cannot open database",
                             "Unable to establish a database connection.\n"
                                      "This example needs SQLite support. Please read "
                                      "the Qt SQL driver documentation for information how "
                                      "to build it.\n\n"
                                      "Click Cancel to exit.", QMessageBox::Ok);
}


#endif // header guard
