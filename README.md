Vende ++

Este projeto foi desenvolvido no âmbito da unidade curricular de Programação e tem como objetivo desenvolver as capacidades dos alunos para esta competência.

Todo o projeto foi realizado por:

	Carlos Miguel da Silva de Freitas (up201504749)
	Luís Noites Martins (up201503344)

————— PROJECTO —————

O programa foi desenvolvido e compilado em visual studio e xcode, pelo que não está garantido o seu integral funcionamento quando compilado por outros softwares.


Neste trabalho, desenvolve-mos todas as competências pretendidas pelo que ao executá-lo o cliente está habilitado a:

- Criar uma loja

- Adicionar/Remover/Editar um cliente (não é possível existir 2 clientes com o mesmo nome)

- Listar de forma formatada e por ordem alfabética as informações de todos ou apenas um cliente

- Listar de forma formatada e por ordem alfabética os produtos disponíveis e o respetivo preço

- Adicionar Transações(atualiza o valor de compras do cliente)

- Listar de forma formatada e por ordem cronológica as transacções:
	a)todas
	b)entre duas datas (verifica se a primeira data é anterior à segunda, e se são ambas válidas)
	c)um dia(verifica se a data é válida)
	d)um cliente

- Recomendar o produto a comprar para os 10 clientes com menor valor de compras(“Bottom10”), procedendo da seguinte forma:
	
	Reune os produtos comuns a este 10 clientes. Posteriormente, encontra os outros clientes (“Clientes Interessantes”) que tenham comprado pelo menos todos os produtos comuns aos Bottom10 + 1.
	De seguida, obtém os produtos dos “Clientes Interessantes” que não foram comprados por todos os Bottom10 simultaneamente, ordenado posteriormente estes do mais frequente para o menos frequente.(produtos não bottom10)
	Por fim, propõem o primeiro produto encontrado que não tenha sido comprado por nenhum dos Bottom10, e se tal não se verifica é proposto o produto menos frequente entre os produtos comprados pelos Bottom10, mesmo que não simultaneamente, e que esteja nos “produtos não bottom10”.

-Recomendar um produto para um cliente da seguinte forma:

	1 - Cria uma matriz com as transações existentes.
	2 - Compara cada transação/cliente com o cliente alvo
	3 - Reune os produtos desse cliente (“produtos a poder sugerir”) seguindo estas 2 condições: 

		a) se este comprou pelo menos um produto não comprado pelo cliente alvo
		b) se é dos o clientes com maior grau de semelhança em relação ao cliente alvo.

	4 - Sugere como produto aquele que é mais frequente entre os “produtos a poder sugerir”


—————  Melhorias  ——————


1 - Verificação da validade de inputs

2 - Verificação de datas

3 - Verificação da existência de ficheiros

