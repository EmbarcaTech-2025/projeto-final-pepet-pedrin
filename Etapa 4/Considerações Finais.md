# Resultados do Ajuste Linear (Distância vs RSSI)

## 1. Modelo Ajustado
O modelo obtido a partir da regressão linear foi:
-0.24 * distancia + -23.13

- -0.24 → inclinação da reta (quanto o RSSI varia a cada aumento unitário da distância).  
- -23.13 → intercepto (valor de RSSI estimado quando a distância = 0).  

Isso significa que:
- A cada 1 metro de aumento na distância, o RSSI diminui em aproximadamente **24 dB**.  
- Quando a distância tende a 0 (extrapolação), o RSSI esperado seria por volta de **-23.13 dBm**.  

## 2. Métrica de Erro
Foi calculado o **Erro Quadrático Médio (MSE)** entre os valores medidos e os previstos:
6.62

- O valor indica o quanto, em média, o modelo se afasta dos pontos reais.
- Quanto menor o MSE, melhor o ajuste.
- Neste caso, o erro mostra que a regressão linear não captura totalmente o comportamento real, pois a relação RSSI–distância tende a ser **logarítmica**.

## 3. Gráfico
- **Pontos azuis:** valores medidos de RSSI em função da distância.  
- **Linha vermelha:** modelo linear ajustado aos dados.  

Esse gráfico permite visualizar:
- A tendência decrescente do RSSI com a distância.  
- O desvio do modelo linear em distâncias maiores (a linha não acompanha bem a curva real dos dados).  

## 4. Interpretação
- O modelo linear simples mostra a tendência geral, mas **não é o mais adequado** para RSSI.  
- O comportamento real segue o **modelo log-distance**, onde RSSI decresce de forma logarítmica em relação à distância.  
- Ainda assim, o ajuste linear pode servir como **aproximação inicial** ou para distâncias curtas.  

## 5. Próximos Passos
- Reajustar o modelo usando `log10(distancia)` em vez de `distancia` para aproximar a fórmula teórica do RSSI.  
- Comparar o MSE entre o modelo linear e o modelo logarítmico.  
- Avaliar qual descreve melhor os dados coletados.  