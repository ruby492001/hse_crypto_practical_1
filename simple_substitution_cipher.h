#pragma once

#include <string>

/// @brief Класс для выполнения шифрования по алгоритму простой замены
class SimpleSubstitutionCipher
{
public:

     /// @brief конструктор класса
     /// @param srcAlphabet - исходный алфавит
     /// @param dstAlphabet - алфавит, в который будет выполнено преобразование(шифрование)
     SimpleSubstitutionCipher( const std::string& srcAlphabet, const std::string& dstAlphabet );

     /// @brief зашифровать текст в соответствии с параметрами, переданными в конструктор
     /// @param openText - открытый текст, который нужно зашифровать
     /// @return шифртекст
     std::string cryptText( const std::string& openText );

     /// @brief расшифровать текст в соответствии с параметрами, переданными в конструктор
     /// @param cryptedText - шифртекст, который необходимо расшифровать
     /// @return открытый текст
     std::string decryptText( const std::string& cryptedText );

     /// @brief зашифровать текст
     /// @param srcAlphabet - исходный алфавит
     /// @param dstAlphabet - алфавит, в который будет выполнено преобразование(шифрование)
     /// @param openText - открытый текст, который нужно зашифровать
     /// @return шифртекст
     static std::string cryptText( const std::string& srcAlphabet, const std::string& dstAlphabet, const std::string& openText );

     /// @brief расшифровать текст
     /// @param srcAlphabet - исходный алфавит
     /// @param dstAlphabet - алфавит, в который будет выполнено преобразование(шифрование)
     /// @param cryptedText - шифртекст, который необходимо расшифровать
     /// @return открытый текст
     static std::string decryptText( const std::string& srcAlphabet, const std::string& dstAlphabet, const std::string& cryptedText );


private:
     /// @brief проверяет, что исходной и целевой алфавит можно использовать(нет повторов символов в каждом из них и совпадает размерность)
     void validateAlphabets();

     /// @brief проверяет строку на наличие повторов
     /// @param str - строка, которая будет проверена
     /// @return true если повторы существуют, иначе false
     bool repeatExists( const std::string& str );

private:
     const std::string srcAlphabet_;
     const std::string dstAlphabet_;
};
