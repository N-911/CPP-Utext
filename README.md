# utext


### Basic

#### The program window must consist of at least three parts:
  * Toolbarshows control elements
  * Text areadisplays file content
  * Tree areashows directory and file structure
  
 
 ### General features:
 
 * open directories and single files
 •list opened directory files and subdirectories in the Tree area. 
    Subdirectories mustbe collapsible
 * open files from the Tree area for reading/editing in the Text area
 * save files after editing
 * copy/cut/paste options in the Toolbar
 * find and replace options in the Toolbar
 * undo and redo options in the Toolbar
 * keyboard shortcuts for all options from Toolbar. Key combinations must be user-friendly
 * keyboard and mouse management of carriage position.
  
  * ability to select a piece of text with the keyboard as well as the mouse
  –the selected text is highlighted
  –copy/cut/paste options are applied only for the selected piece of text
  –the selected portion of text is taken for search when find/replace option isapplied
  
  •horizontal and vertical scroll if the Text area is smaller than the content available
  * Error handling:

### Creative

выделение синтаксиса для исходного кода, языков разметки, файлов конфигурации и другого текста, 
который отображается в организованном или предсказуемом формате

• параметры поиска и замены на основе регулярных выражений

• найти и заменить в нескольких файлах в открытом каталоге и рекурсивно все подкаталоги в нем

• поддержка нескольких кареток, позволяющих печатать сразу в нескольких местах

• поддержка нескольких окон. Один экземпляр программы может запускать несколько полнофункциональных окон 
(например, как это реализовано в Sublime Text)

• базовое форматирование текста (толщина шрифта, стиль шрифта, размер шрифта, отступ, выравнивание, 
маркированный список и т. Д.)

• сворачивание текста. Отрывки текста, которые можно свернуть и вместо этого показать что-то еще

• найти подходящие круглые скобки или скобки с учетом вложенности

• перенос строк. Уместить длинные строки в область отображения без горизонтальной прокрутки

• автозаполнение и автоматический отступ

• разделенный вид области текста для редактирования нескольких файлов с запоминанием курсора текущей 
строки каждого файла

• возможность создавать / удалять / переименовывать файлы или каталоги из области дерева

• обрабатывать как минимум кодировку символов UTF-8, а также поддерживать другие форматы кодирования
• программируемый редактор, в который можно вводить команды или макросы через интерфейс командной строки

• темы для изменения внешнего вида всего пользовательского интерфейса редактора • другие творческие функции




### Resources


UTEXT


###Data structures:
 * Rope

 * Gap buffer

 * piece table


algorithms of text processing

How do collaborative text editors works

What is the difference between plain text and rich text

encoding

Large files

Memento design pattern :
 * https://refactoring.guru/uk/design-patterns/memento
 
 

 Composite design pattern



RESOURCES:

https://www.mimuw.edu.pl/~rytter/BOOKS/text-algorithms.pdf




http://doc.crossplatform.ru/qt/4.7.x/demos-textedit.html

https://habr.com/ru/company/jugru/blog/424763/
