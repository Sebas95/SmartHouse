/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
app.controller("ctlrRegistrar", function ($scope, $http, $location, InforUser) {

    /**
     * Funcion para registrar a un usuario nuevo
     * @returns {undefined}
     */
    $scope.registrarUsuario = function () {
        $http.defaults.withCredentials = false;
        var nombre = document.getElementById("nombre").value;
        var pass = document.getElementById("pass").value;

        console.log(nombre);
        console.log(pass);

        $http({

            url: dirServer + '/users',
            method: 'POST',
            headers: {'Content-Type': 'application/json'},
            data: {nombre: nombre, pass: pass}

        }).then(function (response) {

            var data = response.data;

            status = response.status;
            //console.log(response);
            console.log(status);

            if (status == 200) {
                console.log(response.data);
            } else {
                console.log("invalidos");

            }
        },
                function (error) {
                    manajerError(error.status, $location);
                });
    }



});

