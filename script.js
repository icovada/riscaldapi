$(document).ready(function(){

	$("#sparkline").sparkline([20,20.2,20.5,20.3,20,19.7,19.6,19.8,20 ], {
    type: 'line',
    width: '200',
    height: '200',
    fillColor: undefined,
    spotColor: undefined,
    minSpotColor: '#0000bf',
    maxSpotColor: '#ff0000',
    spotRadius: 3,
    chartRangeMin: 19,
    chartRangeMax: 21,
    normalRangeMin: 19.7,
    normalRangeMax: 20.3,
    drawNormalOnTop: false});
})