#ifndef HEADER_CE7492DAA387A533
#define HEADER_CE7492DAA387A533

#include <QMainWindow>
#include <QMenuBar>
#include <QDockWidget>
#include <QComboBox>
#include <vector>

#include "thetabs.moc"
#include "search_widget.moc"

using namespace std;

class TheWindow;

class TheMenu
{
  public:
    TheMenu(TheWindow *);

    void create_file_action();

    void create_menus();
    void create_menus(TheWindow *);

  protected:
    std::vector<QAction*> m_file_new_actions = {}, m_file_actions = {}, m_edit_actions = {}, m_view_actions = {};
    std::vector<QMenu*>   m_menus = {};
    TheWindow *m_parent;
    QMenuBar  *m_menu_bar;
    QMenu     *m_file_new_menu = new QMenu("&New", nullptr);
};

class TheWindow : public QMainWindow, public TheMenu
{
    Q_OBJECT
  public:
    TheWindow(QWidget * = nullptr);

    void add_dock_widget();
    void add_dock_widgets(uint);
    void add_dock_widgets(vector<QDockWidget*> &);

    void default_settings();

    void enable_tab(bool b = false) { _enable_tab = b; }

  public slots:
    void display(const QString &);

  private:
    TheTabs *mtab_widget = new TheTabs;
    QComboBox *m_search_combo = new QComboBox;
    vector<QDockWidget*> mdock = { };
    QDockWidget* m_search_dock = new QDockWidget("Search");
    SearchWidget *m_search_widget = new SearchWidget;

    bool _enable_tab = true;
};

void TheWindow::display(const QString &)
{
  mtab_widget->m_widgets[0]->setText(m_search_widget->m_search_result);
}

#endif // header guard

