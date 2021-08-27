# Projeto de estação meteorológica

**Nome dos alunos:**
<ul>
	<li>João Paulo Pereira Macêdo - RM: 86353</li>
	<li>Karen Martins Silveira - RM: 85282</li>
	<li>Lucas Pelosi de Almeida - RM: 85987</li>
	<li>Mariana Alves de Oliveira Ribeiro - RM: 86125</li>
	<li>Tiago de Brito Ferreira - RM: 84267</li>
	<li>Vitor Mendes Olivério - RM: 84609</li>
</ul>                    

**Turma:**
2TDSG

**Ano:**
2021

## Objetivo / descrição do Projeto

<p>O projeto foi desenvolvido para a matéria de Disruptive Architectures IOT and IA, do curso de Análise e Desenvolvimento de Sistemas da FIAP.</p>
<p>O intuito do projeto é uma aplicação IoT de estação meteorológica desenvolvido para Smart Cities, na qual faz a coleta de informações por meio de sensores e faz o envio via serial para um fluxo no node-red que publica nos tópicos de cada sensor via MQTT e exibe em um dashboard, caso a velocidade do vento seja maior que 80Km/h é enviado um alerta via twitter.</p>

<b>Dispositivos IoT utilizados:</b>
<ul>
	<li>Arduino Uno</li>
	<li>Fotoresistor LDR: mede a intensidade da luz</li>
	<li>Sensor de temperatura TMP: mede a temperatura</li>
	<li>Frequencímetro: mede a frequência de voltas por segundo</li>
</ul>

## Sotware e plataforma necessários
<ul>
	<li>SimulIDE</li>
	<li>Node-red</li>
</ul>

## Como instalar e configurar 

<b>Passos para utilizar o SimulIDE:</b>
<ol>
<li>Faça o download</li>
	
	https://www.simulide.com/p/downloads.html
<li>Descompacte o arquivo zip</li>
<li>O aplicativo estará na pasta bin</li>
</ol>

<b>Passos para utilizar o Node-red:</b>
<ol>
<li>É necessário a instalação do node.js LTS</li>
	
	https://nodejs.org/en/
<li>Abra o cmd e digite:</li>
	
	npm install -g --unsafe-perm node-red
<li>Para acessar o servidor, acesso no seu browser:</li>
	
	http://localhost:1880
</ol>
<b>Download dos nós no node-red:</b>
<p>Clique no canto superior direito, depois em "Manage palette"</p>
<img src="Configurations/cofigurations-node-red.jpg ">
<b>Faça a instalação desses nós:</b>
<img src="Configurations/nodes-node-red.jpg">
<b>Configuração do nó do Twitter</b>
<ol>
<li>Preencha seus dados e crie uma conta de desenvolvedor no Twitter;</li>
	
		http://developer.twitter.com/
<li>Depois de criada, clique no botão "Create an app" no canto superior direito;</li>
<li>Selecione a opção "Hobbyist", depois "Making a bot";</li>
<li>Preencha com os dados requeridos;</li>
<li>Faça comentários de como você usará o Twitter;</li>
<li>Aceite os termos de uso;</li>
<li>Clique de novo em "Create an app";</li>
<li>Dê um nome ao seu App;</li>
<li>Em "Keys & Tokens" copie os 3 dados informados;</li>
	<img src="Configurations/Key&Tokens-Twitter.jpg">
<li>No node-red dê um duplo clique no nó Twitter Out e clique no lápis do lado direito do Twitter ID;</li>
<li>Informe o seu @ do Twitter, suas Keys e seu Token de acesso, e clique em update;</li>
	<img src="Configurations/credentials-twitter.jpg">
</ol>

## Arquitetura do projeto
<img src="https://user-images.githubusercontent.com/62014653/131036609-5be5094f-ce84-4e74-aaed-f479ecbdb527.png" width="100%">
<h3>Conexões do arduino e componentes: </h3>
<ul>
	<li><b>Porta 2: </b></li>
		<ul>
			<li><b>Clock</b> (encontrado na área Sources): simples fonte que emite uma frequencia baseado na frequencia setada nas propriedades.</li>
			<li><b>Frequencimeter</b> (encontrado na área Meters): mede o sinal de frequencia emitida pelo Clock.</li>
		</ul>
	<li><b>Porta A1: </b> </li>
		<ul>
			<li><b>LDR</b> (encontrado na área Passive): fotoresistor mede a intensidade da luz</li>
			<li><b>Resistor</b> (encontrado na área Meters): resistência de 10kΩ setada nas propriedades</li>
			<li><b>Ground</b> (encontrado na área Sources): fonte de zero voltagem</li>
			<li><b>Rail</b> (encontrado na área Sources): fonte simples de voltagem, voltagem de 5V setada nas propriedades</li>
		</ul>
	<li><b>Porta A0: </b> </li>
		<ul>
			<li><b>Termistor</b> (encontrado na área Passive): sensor TMP que mede a temperatura;</li>
			<li><b>Resistor</b> (encontrado na área Meters): resistência de 10kΩ setada nas propriedades;</li>
			<li><b>Ground</b> (encontrado na área Sources): fonte de zero voltagem;</li>
			<li><b>Rail</b> (encontrado na área Sources): fonte simples de voltagem, voltagem de 5V setada nas propriedades.</li>
		</ul>
	<li><b>Porta serial: </b>
		<ul>
			<li>Para acessá-la clique com a direita do mouse no arduino, depois em "Open Serial Port."</li>
			<li>Para utilizar ela é só clicar no botão "Open" do lado esquerdo.</li>
			<li>Ela abrirá a porta serial no seu computador, provavelmente COM3(porta de saída) e COM4(porta de entrada no node-red)</li>
		</ul>
		
<h3>Nós: </h3>
<ul>
	<li><b>Serial In:</b> A COM4 está recebendo a conexão serial da COM3 que foi aberta no serial do Arudino dentro do SimulIde;</li>
	<li><b>Delay:</b> Faz um delay de 3 segundos;</li>
	<li><b>JSON:</b> O nó JSON está recebendo uma String JSON gerada pelo código do Arduino e converte em um Objeto JavaScript;</li>
	<li><b>Change:</b> Filtra as informações do Objeto JavaScript (Luminosidade, Temperatura, Velocidade do vento);</li>
	<li><b>Mqtt Out:</b> Recebe a mensagem filtrada e publica as mensagens com o contéudo em um MQTT Broker;</li>
	<li><b>Mqtt In:</b> Conecta com o Mqtt Broker e subscreve para mensagens de um tópico específico;</li>
	<li><b>Gauge:</b> Adiciona uma interface Gauge para exibir as informações(Luminosidade, Temperatura, Velocidade do vento) em um dashboard.</li>
	<li><b>Function:</b> Faz uma validação caso a velocidade do vento passe de 80Km/h será retornado um String com um aviso;</li>
	<li><b>Switch:</b> Faz um filtro, caso o Objeto recebido seja do tipo String ele faz o envio ao Twitter Out, caso o Objeto seja do tipo Number ele faz o envio ao Debug;</li>
	<li><b>Twitter Out:</b> Faz a postagem do aviso caso seja necessária.</li>
	<li><b>Debug:</b> Escreve no console o dado recebido(Number).</li>
	<h3>Dados exibidos no <b>Gauge</b>: </h3>
	<ul>
		<li>Luminosidade;</li>
		<li>Temperatura;</li>
		<li>Velocidade do vento.</li>
	</ul>
</ul>

## Para clonar o projeto
<ol>
<li>Faça o download do Git Bash</li>
	
	https://git-scm.com/downloads
<li>Abra o Git Bash e digite:</li>
	
	cd /Users/samsung/Documents
<p>Use o comando "cd" para trocar até o diretório que vc deseja fazer o clone.</p>
	
	ls -l
<p>Use o comando "ls -l" para listar os arquivos que estão no diretório atual.</p>
	
	git clone https://github.com/vitormendes4072/EstacaoMeteoroligica-FelixAI
<p>Use o comando "git clone (link do repositório)" para fazer um clone do repositório.</p>
	
	ls -l
<p>Use o comando "ls -l" para listar os arquivos e cheque se fez o clone do projeto.</p>
</ol>

## Link de vídeo demonstração

[Nosso video no youtube](https://www.youtube.com/watch?v=toQmPJUypIU)


### Referências 

* [Node-red](https://nodered.org/docs/getting-started/local)
* [SimulIDE](https://www.simulide.com/index.html)
* [Node-red-node-twitter](http://lucbors.blogspot.com/2018/09/how-to-use-node-red-to-interact-with.html) 
* [Conexão m2m com Serial](https://www.youtube.com/watch?v=I6YIPL_p-L0)
