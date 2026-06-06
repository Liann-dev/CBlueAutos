#ifndef HOMEUSER_H
#define HOMEUSER_H

#include <string>

void menuUtama(std::string role, std::string login_count, int id_user);
void tampilkanPreferensiTag(int id_user);
void integrasiDatabase(int idUser, std::string referensi[3]);
void recomendation(int userId);

#endif