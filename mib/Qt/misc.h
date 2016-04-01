#ifndef MISC_H
#define MISC_H

QString read_file(const char* fpath)
{
   QFile fl(fpath);
   fl.open(QIODevice::ReadOnly);
   return QTextStream(&fl).readAll();
}

QString read_file(QFile &fl, int from, int to)
{
  QTextStream stream(&fl);
  QString sfile;
  if (fl.open(QIODevice::ReadWrite))
  {
    for(int i = 0; i <= to; ++i)
    {
      if (i >= from)
        sfile += stream.readLine() + "\n";
      else
        stream.readLine();
    }
  }
  return sfile;
}

#endif//MISC_H
