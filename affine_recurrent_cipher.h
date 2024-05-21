#pragma once
#include <string>
#include <cstdint>
#include <vector>


class AffineRecurrentCipher
{
public:
     /// @brief конструктор класса
     /// @param alphabet - алфавит, индексы которого будут использоваться при шифровании и расшифровании
     /// @param key1 - ключ шифрования 1, < a, b >
     /// @param key2 - ключ шифрования 2, < a, b >
     AffineRecurrentCipher( const std::string& alphabet, const std::pair< int64_t, int64_t >& key1, const std::pair< int64_t, int64_t >& key2 );

     /// @brief зашифровать текст в соответствии с параметрами, переданными в конструктор
     /// @param openText - открытый текст, который нужно зашифровать
     /// @return шифртекст
     std::string cryptText( const std::string& openText );

     /// @brief расшифровать текст в соответствии с параметрами, переданными в конструктор
     /// @param cryptedText - шифртекст, который необходимо расшифровать
     /// @return открытый текст
     std::string decryptText( const std::string& cryptedText );

     /// @brief зашифровать текст
     /// @param alphabet - алфавит, индексы которого будут использоваться при шифровании и расшифровании
     /// @param key1 - ключ шифрования 1, < a, b >
     /// @param key2 - ключ шифрования 2, < a, b >
     /// @param openText - открытый текст, который нужно зашифровать
     /// @return шифртекст
     static std::string cryptText( const std::string& alphabet, const std::pair< int64_t, int64_t >& key1,
                                   const std::pair< int64_t, int64_t >& key2, const std::string& openText );

     /// @brief расшифровать текст
     /// @param alphabet - алфавит, индексы которого будут использоваться при шифровании и расшифровании
     /// @param key1 - ключ шифрования 1, < a, b >
     /// @param key2 - ключ шифрования 2, < a, b >
     /// @param cryptedText - шифртекст, который необходимо расшифровать
     /// @return открытый текст
     static std::string decryptText( const std::string& alphabet, const std::pair< int64_t, int64_t >& key1,
                                     const std::pair< int64_t, int64_t >& key2, const std::string& cryptedText );


// private:
     /// @brief расширенный алгоритм Евклида
     /// @param a - первое число
     /// @param a - второе число
     /// @return <g, x, y>
     std::tuple< int64_t, int64_t, int64_t > extendedGCD( int64_t a, int64_t b );


     /// @brief нахождение обратного элемента
     /// @param a - число, для которого ищется обратное число
     /// @param m - модуль числа
     /// @return обратный элемент
     int64_t modInverse(  int64_t a, int64_t m );

private:
     const std::string alphabet_;
     std::vector< std::pair< int64_t, int64_t > > keyList_;
};