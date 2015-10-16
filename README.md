# Шаблон репозитория для выполнения задачи с использованием GCC

Для создания своего задания необходимо клонировать это репозитарий или создать новый на его основе.

При подготовке своего репозитория необходимо удалить файл test.cpp и поместить в него свои файлы, а также внести изменения в makefile для правильной компиляции проекта.
Результат выполнения программы должен записываться в файл - result.dat.

Если при запуске задачи Вы указываете файл с данными, то он будет загружен на сервер под именем datain.dat. В Вашем репозитории не должно быть файлов с таким именем.

Репозиторий должен содержать:
* build.sh
* makefile
* run.sh
* файлы Вашего проекта
* result.dat