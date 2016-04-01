#ifndef MISC_H
#define MISC_H

#include <iostream>

using namespace std;

namespace mvc_utils
{
  namespace file
  {
#ifdef QFILE_H
    QString read_file (QFile &fl, int from, int to)
    {
      QTextStream stream (&fl);
      QString sfile;
      if (fl.open (QIODevice::ReadWrite) )
      {
        for (int i = 0; i <= to; ++i)
        {
          if (i >= from)
            sfile += stream.readLine() + "\n";
          else
            stream.readLine();
        }
      }
      return sfile;
    }
#endif
  }

  namespace io
  {
    ostream& operator<< (ostream &out, const QString &first)
    {
      return out << first.toStdString();
    }

    ostream& operator<< (ostream &out, const QByteArray &first)
    {
      return out << first.data();
    }

 }

}
#endif//MISC_H
