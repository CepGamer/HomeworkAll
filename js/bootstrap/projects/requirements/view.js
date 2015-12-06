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

    map.events.add('click', function (e) {
        if (!map.balloon.isOpen()) {
            var coords = e.get('coords');
            map.balloon.open(coords, {
                contentHeader:'Событие!',
                contentBody:'<p>Кто-то щелкнул по карте.</p>' +
                    '<p>Координаты щелчка: ' + [
                    coords[0].toPrecision(8),
                    coords[1].toPrecision(8)
                    ].join(', ') + '</p>',
                contentFooter:'<sup>Щелкните еще раз</sup>'
            });
        }
        else {
            map.balloon.close();
        }
    });

    map.events.add('contextmenu', function (e) {
        map.hint.open(e.get('coords'), 'Кто-то щелкнул правой кнопкой');
    });
    
    map.events.add('balloonopen', function (e) {
        map.hint.close();
    });
}
