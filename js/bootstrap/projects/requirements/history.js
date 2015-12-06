var points;

function gotoView(id) {
    window.location.href = 'view.html?selected=' + id
}

$.ajax({
    url: "data.json"
}).done(function(data) {
    points = JSON.parse(data);

    for(var x = 0; x < points.routes.length; ++x)
    {
        $('#routes').append('<button type="button" class="btn btn-default" onclick="gotoView(' 
        + x +
        ');">' + points.routes[x].name + 
        '</button>');
    }
});

function createMap(){}
