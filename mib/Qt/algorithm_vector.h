#ifndef QT_ALGORITHM_VECTOR_H
#define QT_ALGORITHM_VECTOR_H

#include <initializer_list>

using std::initializer_list;
using std::vector;

namespace mvc_utils
{
   namespace Qt_utils
   {
      template <typename T>
      T& deinitialize (T& container)
      {
         for (size_t i = 0; i != container.size(); ++i)
         {
            delete container[i];
            container[i] = nullptr;
         }
         return container;
      }

      template <typename T>
      T& deinitialize (T&& container)
      {
         for (size_t i = 0; i != container.size(); ++i)
         {
            delete container[i];
            container[i] = nullptr;
         }
         return container;
      }

      template <typename T>
      T& deinit_n_clear (T& container, size_t no_eles = 1)
      {
         for (size_t i = 0; i != container.size(); ++i)
         {
            delete container[i];
            container[i] = nullptr;
         }
         container.clear();
         return container;
      }

      template <typename T>
      vector<T*> initialize (size_t no_eles = 1)
      {
         vector<T*> container;
         for (size_t i = 0; i != no_eles; ++i)
            container.push_back (new T);
         return container;
      }

      template <typename T>
      vector<T*>& initialize (vector<T*>& container, size_t no_eles = 1)
      {
         for (size_t i = 0; i != no_eles; ++i)
            container.push_back (new T);
         return container;
      }

      template <typename T, typename T2>
      vector<T*>& initialize (vector<T*>& container, T2* parent, size_t no_eles = 1)
      {
         for (size_t i = 0; i != no_eles; ++i)
            container.push_back (new T (parent) );
         return container;
      }

      template <typename T, typename ...T2>
      vector<T*>& initialize (vector<T*>& container, size_t no_eles, T2&& ...parent)
      {
         for (size_t i = 0; i != no_eles; ++i)
            container.push_back (new T (parent...) );
         return container;
      }

      template <typename T, typename T2>
      T& initialize_actions (T& container, T2* parent, size_t no_eles = 1)
      {
         for (size_t i = 0; i != no_eles; ++i)
            container.push_back (new QAction(parent) );
         return container;
      }

      template <typename T, typename T2>
      void add_actions_to (T &parent, T2 &init_list, initializer_list<int> &&separator_list = {})
      {
         auto b = separator_list.begin();
         for (size_t i = 0; i != init_list.size(); ++i)
         {
            parent->addAction (init_list[i]);
            if ( (b != separator_list.end() ) && (i == *b) )
            {
               parent->addSeparator();
               ++b;
            }
         }
      }

      template <typename T, typename T2>
      void set_texts (T& container, std::initializer_list<T2>&& names)
      {
         auto b = names.begin();
         for (size_t i = 0; (i != (container.size() ) ) && (b != names.end() ); ++i)
            container[i]->setText (*b++);
      }

      template <typename T, typename T2>
      void set_titles (T& container, std::initializer_list<T2>&& names)
      {
         auto b = names.begin();
         for (size_t i = 0; (i != (container.size() ) ) && (b != names.end() ); ++i)
            container[i]->setTitle (*b++);
      }

      namespace layouts
      {
         template <typename T, typename T2>
         void add_widgets(T* layout, initializer_list<T2*> &&widgets)
         {
            auto b = widgets.begin();
            for (size_t i = 0; (i != (layout.size() ) ) && (b != widgets.end() ); ++i)
               layout[i]->addWidget (*b++);
         }

         template <typename T, typename T2>
         void add_widgets(T* layout, vector<T2*> &widgets)
         {
            auto b = widgets.begin();
            for (size_t i = 0; (i != (layout.size() ) ) && (b != widgets.end() ); ++i)
               layout[i]->addWidget (*b++);
         }
      }

      namespace signal_slot
      {
         template <typename Sender, typename Slot, typename Receiver, typename Signal>
         void connect (initializer_list<Sender>&& sender, initializer_list<Signal>&& signal,
                       initializer_list<Receiver>&& receiver, initializer_list<Slot>&& slot)
         {
            auto b_sender = sender.begin();
            auto b_slot = slot.begin();
            auto b_receiver = receiver.begin();
            auto b_signal = signal.begin();

            for ( ; b_sender != sender.end(); ++b_sender, ++b_signal, ++b_receiver, ++b_slot)
            {
               QObject::connect (*b_sender, *b_signal, *b_receiver, *b_slot);
            }
         }

         template <typename Sender, typename Slot, typename Receiver, typename Signal>
         void connect (initializer_list<Sender>&& sender, Signal* signal,
                       Receiver* receiver, initializer_list<Slot>&& slot)
         {
            auto b_sender = sender.begin();
            auto b_slot = slot.begin();

            for ( ; b_sender != sender.end(); )
               QObject::connect (*b_sender++, signal, receiver, *b_slot++);
         }

         template <typename Sender, typename Slot, typename Receiver, typename Signal>
         void connect (Sender* sender, initializer_list<Signal>&& signal, initializer_list<Receiver>&& receiver,
                       initializer_list<Slot>&& slot)
         {
            auto b_slot = slot.begin();
            auto b_receiver = receiver.begin();
            auto b_signal = signal.begin();

            for ( ; b_slot != slot.end();)
               QObject::connect (sender, *b_signal++, *b_receiver++, *b_slot++);
         }

         template <typename Sender, typename Slot, typename Receiver, typename Signal>
         void connect (Sender* sender, initializer_list<Signal>&& signal, Receiver* receiver,
                       initializer_list<Slot>&& slot)
         {
            auto b_slot = slot.begin();
            auto b_signal = signal.begin();

            for ( ; b_slot != slot.end(); )
               QObject::connect (sender, *b_signal++, receiver, *b_slot++);
         }

         template <typename Sender, typename Slot, typename Receiver, typename Signal>
         void connect_r (Sender* sender, Signal&& signal, Receiver* receiver,
                         initializer_list<Slot>&& slot)
         {
            auto b_slot = slot.begin();
            auto b_signal = signal.begin();

            for ( ; b_slot != slot.end(); )
               QObject::connect (sender, SIGNAL (*b_signal++), receiver, SLOT (*b_slot++) );
         }
      }

      namespace qsettings
      {
#ifdef QSETTINGS_H
         template <class Type_Value>
         void set_values(QSettings& _sett, initializer_list<cchar*>&& _name, initializer_list<Type_Value>&& _vals)
         {
            for ( auto it = _vals.begin(); it != _vals.end(); ++it )
            {
               _sett.setValue(_name, *it);
            }
         }

         template <class Type_Value>
         void set_values_w_group(QSettings& _sett, cchar* _begin_group,
                                 initializer_list<cchar*>&& _name,
                                 initializer_list<Type_Value>&& _vals)
         {
            _sett.beginGroup(_begin_group);
            set_values(_sett, _name, _vals);
            _sett.endGroup();
         }
#endif // QSETTINGS_H
      }
   }
}

#endif//QT_ALGORITHM_VECTOR_H
