function createMap(){
    var query = parseQuery();
    var selected = 0;
    if(query.selected != undefined)
        selected = query.selected;
        
    objectManager = new ymaps.ObjectManager({
        // Чтобы метки начали кластеризоваться, выставляем опцию.
        clusterize: false,
        // ObjectManager принимает те же опции, что и кластеризатор.
        gridSize: 32
    });

    map = new ymaps.Map("map", {
        center: [0, 0],
        zoom: 11
    }, {
        balloonMaxWidth: 200,
        searchControlProvider: 'yandex#search'
    });    

    // Чтобы задать опции одиночным объектам и кластерам,
    // обратимся к дочерним коллекциям ObjectManager.
    objectManager.objects.options.set('preset', 'islands#greenDotIcon');
    objectManager.clusters.options.set('preset', 'islands#greenClusterIcons');

    map.geoObjects.add(objectManager);
    
    $.ajax({
        url: "data.json"
    }).done(function(data) {
        points = JSON.parse(data);
        map.setCenter(points.routes[selected].features[0].geometry.coordinates);
        objectManager.add(points.routes[selected]);
    });
}
