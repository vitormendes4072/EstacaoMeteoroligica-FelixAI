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
<p>O intuito do projeto é uma aplicação IoT de estação meteorológica desenvolvido para Smart Cities, na qual faz a coleta de informações por meio de sensores e faz o envio via serial para um um fluxo no node-red que publica nos tópicos de cada sensor via MQTT e exibe em um dashboard, caso a velocidade do vento seja maior que 80Km/h é enviado um alerta via twitter.</p>

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
<img src="cofigurations-node-red.jpg ">
<p><b>Faça a instalação desses nós:</b></p>
<img src="nodes-node-red.jpg">

## Arquitetura do projeto

<img src="https://user-images.githubusercontent.com/62014653/130795367-226e9f63-507f-4d18-aaf3-24a76870a9f8.png" width="90%">
<h3>Fluxo do Node-Red </h3>
<img src="FluxoNodeRed.png" width="60%">
<h3>Nós: </h3>
<ul>
	<li><b>Serial In:</b> A COM4 está recebendo a conexão serial da COM3 que foi aberta no serial do Arudino dentro do SimulIde</li>
	<li><b>JSON:</b> O nó JSON está recebendo o arquivo JSON gerado pelo código do Arduino</li>
	<li><b>Change/Set:</b> Filtra as informações do json (Luminosidade, Temperatura, Velocidade do vento)</li>
	<li><b>Mqtt Out:</b> recebe a mensagem filtrada e publica as mensagens com o contéudo</li>
	<li><b>Mqtt In:</b> conecta com o Mqtt Out e faz o envio para o Gauge</li>
	<li><b>Gauge:</b> adiciona uma interface Gauge para exibir as informações em um dashboard</li>
	<h3>Dados exibidos</h3>
	<ul>
		<li>Luminosidade</li>
		<li>Temperatura</li>
		<li>Velocidade do vento</li>
	</ul>
</ul>

## Para clonar o projeto
<ol>
<li>Faça o download do Git Bash</li>
	
	https://git-scm.com/downloads
<li>Abra o Git Bash e digite<li>
	
	cd /home/iot
	ls -l
	git clone https://github.com/vitormendes4072/EstacaoMeteoroligica-FelixAI
	ls -l
</ol>
<p>Use o comando "cd" para trocar até o diretório que vc deseja fazer o clone.</p>
<p>Use o comando "ls -l" para listar os arquivos que estão no diretório atual.</p>
<p>Use o comando "git clone (link do repositório)" para fazer um clone do repositório.</p>

## Link de vídeo demonstração

Adicione o link para assistir ao vídeo do projeto funcionando.

[Link para o video youtube](https://www.youtube.com/watch?v=xva71wynxS0)


### Referências 

* [Node-red](https://nodered.org/docs/getting-started/local)
* [SimulIDE](https://www.simulide.com/index.html)
