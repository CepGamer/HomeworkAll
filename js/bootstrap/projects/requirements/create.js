var cur = 0;
var s;

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
    });
    
    map.events.add('click', function (e) {        
        var coords = e.get('coords');
        var x = '{ "type": "Feature", "id": ' + cur + ', "geometry": {"type": "Point", "coordinates": [' 
        + coords[0].toPrecision(6) + ', ' + coords[1].toPrecision(6) + 
        ']}, "properties": {"balloonContent": "' + (cur == 0 ? "Старт" : ("Контрольная точка " + cur)) + 
        '", "clusterCaption": "Контрольная точка", "hintContent": ""}}';
        cur++;
        objectManager.add(x);
    });
}

function saveButton() {
    var newRoute = objectManager.objects.getAll();
    points.routes[points.routes.length] = {type: "FeatureCollection", features: newRoute};
    try {
        $.ajax({
            type: "POST",
            url: "data.json",
            data: points
        });
        alert("Успешно сохранено!");
        objectManager.objects.removeAll();    
    } catch (error) {
        
    }
}

function removeButton() {
    objectManager.objects.removeAll();
}
