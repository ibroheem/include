#ifndef GENERIC_TEXT_EDIT_H
#define GENERIC_TEXT_EDIT_H

#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QMimeData>

template <typename T>
QString to_qstring (T num, int base = 10)
{
   return QString().number (num, base);
}

class TheText : public QTextEdit
{
   public:
      TheText(QWidget * = nullptr);

      ExtraSelection& find_next(int);
      ExtraSelection& find_prev(int);
      ExtraSelection& find_text(c_qstring&, int opt);

      void load_file(const QString&);
      void load_image(const QMimeData*);

   protected:
      void dragEnterEvent(QDragEnterEvent *);
      void dropEvent(QDropEvent *);

   private:
      QList<QTextEdit::ExtraSelection> extra_selections;
      QTextEdit::ExtraSelection current_search_sel;
      int m_text_found_pos;
};

TheText::TheText(QWidget *p) : QTextEdit(p)
{
   setAcceptDrops(true);
}

QTextEdit::ExtraSelection& TheText::find_text(c_qstring &search_string, int opt)
{
   switch (opt)
   {
      case 1:
      {
         m_text_found_pos = 0;
         extra_selections.clear();
         moveCursor(QTextCursor::MoveOperation::Start);

         TheText::ExtraSelection xtra_sel;
         while(find(search_string, QTextDocument::FindFlag::FindWholeWords))
         {
            xtra_sel.cursor = textCursor();
            xtra_sel.format.setForeground(Qt::GlobalColor::red);

            extra_selections.append(xtra_sel);
         }
         setExtraSelections(extra_selections);
         current_search_sel = extra_selections.back();
      } break;

      case 2:
      {
      } break;

      case 3:
      {
      } break;
   }
   return current_search_sel;
}

QTextEdit::ExtraSelection& TheText::find_next(int step = 1)
{
   for (int i = 0; i < extra_selections.size(); ++i)
   {
      if (extra_selections[i].cursor == current_search_sel.cursor)
      {
         if (i == extra_selections.size() - 1)
            i = -1;

         setTextCursor(extra_selections[i + step].cursor);
         current_search_sel = extra_selections[i + step];
         break;
      }
   }
   return current_search_sel;
}

QTextEdit::ExtraSelection& TheText::find_prev(int step = 1)
{
   for (int i = 0; i < extra_selections.size(); ++i)
   {
      if (extra_selections[i].cursor == current_search_sel.cursor)
      {
         if (i == 0)
            i = extra_selections.size();

         setTextCursor(extra_selections[i - step].cursor);
         current_search_sel = extra_selections[i - step];
         break;
      }
   }
   return current_search_sel;
}

void TheText::load_image(const QMimeData* source)
{
   QImage image = qvariant_cast<QImage>(source->imageData());
   QTextCursor cursor = this->textCursor();
   QTextDocument *document = this->document();
   document->addResource(QTextDocument::ImageResource, QUrl("image"), image);
   cursor.insertImage("image");
}

void TheText::dragEnterEvent(QDragEnterEvent *event)
{
   if (event->mimeData()->hasUrls())
      event->acceptProposedAction();
}

void TheText::dropEvent(QDropEvent *event)
{
   if (event->mimeData()->hasUrls())
   {
      for(QUrl &url : event->mimeData()->urls())
      {
         load_file(url.path());
      }
   }
}

void TheText::load_file(const QString& _fpath)
{
   QFile fl(_fpath);
   fl.open(QIODevice::ReadOnly);

   setText(QTextStream(&fl).readAll());
   moveCursor(QTextCursor::Start);
}

#endif//GENERIC_TEXT_EDIT_H
