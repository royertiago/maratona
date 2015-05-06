#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

/* Normaliza a cadeia de caracteres para o formato que usaremos na solução.
 * No formato da solução, str[0] é a altura do tambor mais próximo
 * à saída da fechadura (tranca), e str[n] é o mais distante.
 * Assumiremos também que não há zeros ao final da fechadura.
 *
 * Observe que, sob esta normalização, uma chave inserida parcialmente
 * é o mesmo que pegar um sufixo de uma chave inserida por completo;
 * então, "quebrando" a chave em pedaços, podemos assumir, na função join,
 * que as duas chaves foram colocadas até o final.
 */
std::string normalize( std::string str ) {
    int i;
    for( i = 0; str[i] == '0'; i++ )
        ;
    str = str.substr(i);
    return std::string( str.rbegin(), str.rend() );
}

/* join( chaveA, chaveB )
 * Retorna o resultado de juntar as chaves A e B, na mesma posição,
 * assumindo que ambas as chaves são colocadas até o final.
 */
std::string join( std::string a, std::string b ) {
    std::string ret;

    /* Sob a hipótese da normalização, a implementação de join fica mais simples.
     * a[0] e b[0] ficarão na posição 0 da chave resultante;
     * a[1] e b[1] ficarão na posição 1 da chave resultante;
     * e assim por diante.
     */
    auto it = a.begin();
    auto jt = b.begin();
    while( it != a.end() && jt != b.end() ) {
        ret.push_back( std::max(*it, *jt) );
        ++it;
        ++jt;
    }

    /* Se uma das chaves for menor do que a outra,
     * precisamos completar 'ret' sem extrair o máximo.
     *
     * O código abaixo funciona pois ao menos um dos iteradores
     * já atingiu o fim do seu respectivo contêiner.
     */
    while( it != a.end() )
        ret.push_back( *it++ );
    while( jt != b.end() )
        ret.push_back( *jt++ );

    return ret;
}

/* key_list conterá a lista de todas as possíveis combinações de chaves,
 * em todas as possíveis posições.
 * Por exemplo, se nós temos as chaves "13" e "22", normalizadas para "31" e "22",
 * a lista conterá as chaves "13", "22", "1", "3", "2", "23", e "32".
 *
 * O algoritmo funciona e continua exponencial se trocarmos std::set
 * por std::vector; entretanto, experimentando com os casos de teste oficiais,
 * usar std::set parece ser 5 a 10 vezes mais rápido,
 * o que indica que os casos de teste não foram muito bem feitos
 * para evitar redundâncias e maximizar a quantidade de possíveis chaves.
 */
std::set< std::string > key_list;

/* Adiciona todas as combinações possíveis de 'key'
 * com as chaves atuais de key_list à key_list.
 *
 * Observe que temos de tomar cuidado para inserir não apenas
 * todos os sufixos da chave,
 * mas também todas as junções de todos os sufixos
 * com os valores que já estão em key_list.
 */
void push_key( std::string key ) {
    std::vector< std::string > additional_keys;

    /* Observe que estamos adicionando a chave key.substr(key.size()).
     * Esta chamada retorna uma cadeia de caracteres vazia.
     * Isto representa a chave não inserida da fechadura;
     * o único caso em que ela aparece é quando a própria fechadura
     * possui o valor "00000000", pois normalize("00000") == "".
     *
     * Portanto, caso troquemos o '<=' por um '<', precisamos tratar
     * o caso especial de uma fechadura destrancada.
     */
    for( int i = 0; i <= key.size(); i++ )
        additional_keys.push_back( key.substr(i) );

    for( const auto & str : key_list )
        for( int i = 0; i < key.size(); i++ )
            additional_keys.push_back( join(str, key.substr(i)) );

    key_list.insert( additional_keys.begin(), additional_keys.end() );
}

/* Resolve o problema.
 * Observe que, caso alguma combinação das chaves, em diversas posições,
 * consiga abrir a fechadura, então o join de todas estes pedaços de chave
 * retorna lock --- portanto, lock está em key_list.
 *
 * Poderia ter usado key_list.count, mas o aceleramento foi imperceptível,
 * portanto eu deixei assim para facilitar a troca de std::set para std::vector.
 */
char solve( std::string lock ) {
    for( const auto & str : key_list )
        if( lock == str )
            return 'S';
    return 'N';
}

int main() {
    int i = 1;
    int k, l;
    while( std::cin >> k >> l && k != 0 && l != 0 ) {
        std::cout << "Caso: #" << i++ << '\n';

        key_list.clear();
        for( int t = 0; t < k; t++ ) {
            std::string key;
            std::cin >> key;
            push_key( normalize(key) );
        }

        for( int t = 1; t <= l; t++ ) {
            std::string lock;
            std::cin >> lock;
            std::cout << t << ": " << solve( normalize(lock) ) << '\n';
        }
    }
    return 0;
}
