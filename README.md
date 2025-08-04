Desafio WAR Estruturado – Conquista de Territórios
Bem-vindo ao Desafio WAR Estruturado! Inspirado no famoso jogo de estratégia, este desafio convida você a programar diferentes versões do jogo WAR, evoluindo seus conhecimentos em C à medida que avança pelos níveis Novato, Aventureiro e Mestre.
A empresa MateCheck contratou você para criar uma versão estruturada do WAR. Cada nível propõe novas funcionalidades, conceitos e desafios de programação. Você escolhe por onde começar!
________________________________________

🧩 Nível Novato: Cadastro Inicial dos Territórios
Neste nível, seu desafio é criar um sistema básico de cadastro de territórios dominados por diferentes exércitos.

🎯 Objetivo:
•	Criar uma struct chamada Territorio.
•	Usar um vetor estático de 5 elementos para armazenar os territórios.
•	Cadastrar os dados de cada território: Nome, Cor do Exército, e Número de Tropas.
•	Exibir o estado atual do mapa.

⚙️ Funcionalidades:
•	Leitura de dados pelo terminal (fgets e scanf).
•	Impressão organizada dos dados de todos os territórios.

💡 Conceitos abordados:
•	Estrutura (struct)
•	Vetor estático
•	Entrada/saída com scanf, fgets, e printf

📥 Entrada:
O usuário digita o nome do território, a cor do exército dominante e o número de tropas para cada um dos 5 territórios.

📤 Saída:
O sistema imprime os dados de cada território, como:
 ________________________________________

🧗‍♂️ Nível Aventureiro: Batalhas Estratégicas
Prepare-se para simular ataques! Agora que os territórios estão cadastrados, é hora de adicionar dinâmica ao jogo.

🎯 Objetivo:
•	Substituir o vetor estático por alocação dinâmica com calloc.
•	Criar uma função para simular ataques entre dois territórios.
•	Utilizar números aleatórios para representar dados de batalha.

🆕 Diferenças em relação ao Nível Novato:
•	Alocação dinâmica de memória usando calloc.
•	Uso de ponteiros para manipular os territórios.
•	Inclusão de um laço interativo que permite ao jogador escolher territórios para atacar e defender.
•	Simulação de dados de ataque e defesa com rand().

⚙️ Funcionalidades:
•	Cadastro dos territórios igual ao nível Novato.
•	Fase de ataque: o jogador escolhe territórios para atacar e defender.
•	Lógica de batalha:
o	Se o atacante vence, o defensor perde 1 tropa.
o	Se o defensor perde todas as tropas, o território é conquistado.
o	Empates favorecem o atacante.

💡 Conceitos abordados:
•	Ponteiros
•	Alocação dinâmica com calloc e liberação com free
•	Números aleatórios com rand() e srand()
•	Modularização básica com funções

📥 Entrada:
O jogador escolhe:
•	Território atacante (1 a 5)
•	Território defensor (1 a 5)

📤 Saída:
O programa exibe o resultado do dado de cada lado e as consequências da batalha.
________________________________________

🧠 Nível Mestre: Missões e Modularização Total
Agora você é o mestre da guerra! Este nível traz lógica mais elaborada, modularização completa e um sistema de missões.

🎯 Objetivo:
•	Dividir o código em funções bem definidas.
•	Implementar um sistema de missões para o jogador.
•	Verificar se a missão foi cumprida.
•	Utilizar boas práticas de programação com const, ponteiros e passagem por valor.

🆕 Diferenças em relação ao Nível Aventureiro:
•	Todo o código está modularizado em funções organizadas.
•	Missões aleatórias são atribuídas ao jogador:
1.	Destruir o exército Verde
2.	Conquistar 3 territórios
•	Verificação da missão é feita com lógica apropriada.
•	O jogador interage por meio de um menu.

⚙️ Funcionalidades:
•	Inicialização automática dos territórios.
•	Menu principal com três opções:
1.	Atacar
2.	Verificar Missão
3.	Sair
•	Fase de ataque idêntica ao nível Aventureiro.
•	Ao verificar a missão, o sistema informa se o jogador venceu ou ainda não cumpriu o objetivo.

💡 Conceitos abordados:
•	Modularização
•	Const correctness (const para leitura segura)
•	Estruturação em múltiplas funções
•	Passagem por referência

📥 Entrada:
•	Ações do jogador via menu (1 - Atacar, 2 - Verificar Missão, 0 - Sair)
•	Escolha dos territórios para ataque

📤 Saída:
•	Mapa atualizado
•	Resultados das batalhas
•	Verificação da missão
•	Mensagem de vitória ao completar o objetivo
________________________________________

🏁 Conclusão
Com este desafio WAR Estruturado, você praticará fundamentos essenciais da linguagem C de forma divertida e progressiva. Cada nível foi pensado para desenvolver diferentes habilidades:
•	🟢 Novato: Estruturas e entrada/saída
•	🔵 Aventureiro: Ponteiros, memória dinâmica e lógica de jogo
•	🟣 Mestre: Modularização, design limpo e mecânica de missões

🚀 Boa sorte! Avance nos níveis e torne-se um mestre da programação estratégica!
Equipe de Ensino - MateCheck content_copy


