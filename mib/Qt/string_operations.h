#ifndef STRING_OPERATIONS_H_QT
#define STRING_OPERATIONS_H_QT

#include <QString>
#include <mib/typedefs.h>

namespace mvc_utils
{
  namespace string_operations_Qt
  {
    QString from_utf8 (cchar *c)
    {
      return QString::fromUtf8(c);
    }

    std::string to_std_string (const QString &s)
    {
      return s.toStdString();
    }

    QString to_qt_string (const std::string &s)
    {
      return QString (s.c_str() );
    }

    template <typename T>
    T to_num (const QChar &num, int base = 10)
    {
      return QString (num).toLongLong (0, base);
    }

    template <typename T>
    T to_num (const QString &num, int base = 10)
    {
      return num.toLongLong (0, base);
    }

    template <typename T>
    QString to_qstring (T num, int base = 10)
    {
      return QString().number (num, base);
    }

    QString to_utf8 (cchar *c)
    {
      return QString (c).toUtf8();
    }

    inline QString file_ext (QString &fname, char separator = '.')
    {
      int i = fname.count (separator) ;
      return fname.section (separator, i, i).prepend ('.');
    }

    inline QString file_name_w_ext (QString&& fname, char separator = '/')
    {
      int i = fname.count (separator) ;
      return fname.section (separator, i, i);
    }

    inline QString file_name_w_ext (QString &fname, char separator = '/')
    {
      return file_name_w_ext (std::forward < QString && > (fname), separator);
    }

    inline QString file_name_w_ext (const QString &fname, char separator = '/')
    {
      return file_name_w_ext (std::forward <const QString & > (fname), separator);
    }

    inline QString file_name_wo_ext (QString&& fname, char separator = '/')
    {
      QString stemp = file_name_w_ext (fname, separator);
      separator = '.';
      return stemp.remove (stemp.lastIndexOf (separator), stemp.size() );
    }

    inline QString file_name_wo_ext (QString &fname, char separator = '/')
    {
      return file_name_wo_ext (std::forward < QString && > (fname), separator);
    }
  }

}

#endif //STRING_OPERATIONS_H_QT

