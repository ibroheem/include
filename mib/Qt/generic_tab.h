#ifndef GENERIC_TAB_H
#define GENERIC_TAB_H

#include <QTabWidget>
#include <QMessageBox>
#include "mib/Qt/algorithm.h"

using std::vector;
using namespace mvc_utils;

class TheTabs : public QTabWidget
{
    Q_OBJECT
  public:
    TheTabs(QWidget * = nullptr);

    template <class T>
    T* insert_tab(int _index, const QString &, const QIcon & = QIcon(""));

    template <class T>
    T* insert_tab(int _index, T*, const QString &name = "", const QIcon &icon = QIcon(""));

    template <class T1>
    T1* add_tab(const QString &, const QIcon & = QIcon(""));

    template <class T>
    T* add_tab() { return insert_tab<T>(QString("Untitled"), QIcon("")); }

    template <class T>
    T* add_tab(T*, const QString &name = "", const QIcon &icon = QIcon(""));

    bool crazy() { return ((count() == 0) ? true : false); }

    template <class T>
    T* current_widget() { return qobject_cast<T*>(mtexts[currentIndex()]); }

    void swap_widget(int, int);

    template <class T>
    T* widget_at(int i) { return qobject_cast<T*>(widget(i)); }

  public Q_SLOTS:
    void activate_tab(int);
    void close_tab(int);
    void close_current_tab() { close_tab(currentIndex()); }
    void move_tab(int);
    void move_tab_helper(int, int);

  private:
    QList<QWidget*>  mtexts = {};
};

TheTabs::TheTabs(QWidget *p) : QTabWidget(p)
{
  setMovable(true);
  setTabsClosable(true);

  connect(this, SIGNAL(currentChanged(int)), this, SLOT(activate_tab(int)));
  connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(close_tab(int)));
}

template <class T>
T* TheTabs::insert_tab(int _index, const QString &name, const QIcon &icon)
{
  mtexts.push_back(new T);
  insertTab(_index, mtexts[mtexts.size() - 1], icon, name);
  return qobject_cast<T*>(mtexts[mtexts.size() - 1]);
}

template <class T>
T* TheTabs::insert_tab (int _index, T *_widget, const QString &name, const QIcon &icon)
{
  mtexts.push_back (_widget);
  insertTab(_index, mtexts[mtexts.size() - 1], icon, name);
  return qobject_cast<T*> (mtexts[mtexts.size() - 1]);
}

template <class T>
T* TheTabs::add_tab(const QString &name, const QIcon &icon)
{
  mtexts.push_back(new T);
  addTab(mtexts[mtexts.size() - 1], icon, name);
  return qobject_cast<T*>(mtexts[mtexts.size() - 1]);
}

template <class T>
T* TheTabs::add_tab(T *_widget, const QString &name, const QIcon &icon)
{
  mtexts.push_back (_widget);
  addTab (mtexts[mtexts.size() - 1], icon, name);
  return qobject_cast<T*>(mtexts[mtexts.size() - 1]);
}

void TheTabs::activate_tab(int i)
{
  QString s = tabText(i).append(QString("%1").arg(i));
  if (i >= 0)
  {
    s.remove(s.size() - 1, 1);
    setCurrentIndex(i);
    setTabText(i, s);
  }
}

void TheTabs::close_tab(int i)
{
  if (i >= 0)
  {
    mtexts.removeAt(i);
    removeTab(i);
    //delete mtexts[i];
  }
}

void TheTabs::move_tab_helper(int from, int to)
{
  mtexts.swap(from, to);
}

void TheTabs::move_tab(int i)
{
  activate_tab(i);
}

void TheTabs::swap_widget(int fr, int to)
{
  //
}

#endif//GENERIC_TAB_H
