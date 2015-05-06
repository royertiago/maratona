/* Problema C da Maratona Catarinense de Programação de 2013.
 *
 * Teorema: este problema, com cadeias de caracteres de tamanho arbitrário,
 * é NP-completo.
 *
 * Demonstração: Reduziremos CNF-SAT para este problema.
 * Para uma fórmula lógica com N variáveis e M cláusulas,
 * usaremos uma fechadura de tamanho 2M + 3
 * e N + 1 chaves de tamanho 2M + 3.
 * Apenas precisaremos de pinos de alturas 0, 1, 2 e 3.
 *
 * As N primeiras chaves codificarão variáveis.
 * A ideia é restringir as posições destas chaves a apenas duas posições.
 * Interpretaremos a primeira posição como atribuir V à variável correspondente,
 * e a segunda posição como atribuir F à variável correspondente.
 *
 * Elas terão três pinos de tamanho 2, nas posições 0, M+1 e 2M+2.
 * Todos os demais pinos possuirão tamanho 1 ou 0.
 * A fechadura também terá três pinos de tamanho 2, nestas mesmas posições
 * (com exceção do pino do meio, que terá altura 3; justificaremos mais tarde).
 * Todos os outros pinos da fechadura terão altura 1.
 *
 * Observe que o pino da frente das chaves possui altura 2,
 * que, por ser mais alto que a maior parte dos pinos,
 * possui apenas três posições possíves em que pode ser encaixado:
 * na posição 0, M+1 ou 2M+2. Todos estes encaixes são válidos.
 * Embora não tenhamos conseguido restringir o posicionamento
 * para apenas duas posições, em uma das posições a chave não interfere
 * na combinação gerada, portanto, isto é bom o bastante.
 *
 * Interpretaremos "Inserir até a metade" como atribuir falso à variável
 * e "Inserir até o fundo" como atribuir verdadeiro à variável.
 *
 * Agora, às cláusulas: Se a variável K aparece na cláusula J
 * como um literal positivo, escolha o pino J+1 na chave K como 1;
 * caso contrário, escolha como 0.
 * Se a variável K aparece na cláusula J como um literal negativo,
 * escolha o pino M+1 + J+1 como 1; caso contrário, escolha como 0.
 *
 * Concentremo-nos nos M primeiros pinos da fechadura (após o pino inical,
 * de tamanho 2). Caso escolhamos a variável K como falsa
 * (isto é, inserimos-na até a metade), os M+2 últimos pinos da chave
 * serão inseridos como os M+2 primeiros pinos da fechadura.
 * Portanto, se o pino M+1 + J+1 for 1, nós já garantimos que
 * o pino J+1 da fechadura fique em 1. Observe que o pino M+1 + J+1
 * é 1 exatamente quando a cláusula J possuir K como literal negativo;
 * isto é, o pino J+1 na fechadura representa o valor-verdade
 * da cláusula J na fórmula CNF da entrada.
 * Similarmente, se K for verdadeiro, então todos os pinos
 * que correspondem a cláusulas com K como literal positivo
 * ficarão "acesos" na fechadura.
 *
 * Observe que um pino só fica "aceso" se alguma das chaves o "acender".
 * Portanto, qualquer posicionamento das chaves
 * que "acenda" todos os M+1 primeiros pinos da fechadura
 * codifica uma atribuição que satisfaz a fórumula da entrada,
 * e vice-versa.
 * (Podemos entender a não-inserção da chave como uma variável não-atribuida.
 * Se com uma atribuição parcial já conseguimos satisfazer à fórmula,
 * escolher valores arbitrários para as demais variáveis
 * resulta numa atribuição que satisfaz à formula,
 * portanto este detalhe não nos traz problemas.)
 *
 * Falta resolver os M+1 últimos pinos.
 * Para isso, adicionaremos mais uma chave, específica para esta situação.
 * Ela também conterá os três pinos de "posicionamento",
 * mas o pino central terá tamanho 3. É a única chave com um pino deste tamanho;
 * como a fechadura também possui um pino de tamanho 3,
 * esta chave é de "uso obrigatório" na solução.
 * Escolhemos os pinos M+2 até 2M+1 desta chave como 1,
 * apenas para garantir que os últimos pinos da fechadura sejam sempre preenchidos;
 * e escolheremos os demais pinos como 0, para não influenciar
 * na organização descrita no parágrafo anterior.
 *
 * Assim, qualquer atribuição satisfazível codifica um posicionamento das chave
 * que resolve os M+1 primeiros pinos, e, usando esta chave adicional,
 * nós resolvemos "no braço" os M+2 últimos;
 * e, dado um posicionamento de chaves, conseguimos reconstruir
 * a atribuição correspondente que satisfaz a fórmula.
 *
 * Portanto, todo problema em NP é redutível a este problema.
 * Q.E.D.
 */
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
