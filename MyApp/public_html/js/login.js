/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

app.controller("ctlrLogin", function ($scope, $http, $location) {


    /**
     * Funcion para hacer la validacion de inicio de sesion
     * @returns {undefined}
     */
    $scope.ingresar = function () {
        var nombre = document.getElementById("login").value;
        var pass = document.getElementById("pass").value;
        //$location.path("/interfaz");
        $http.defaults.withCredentials = false;
        $http({
            url: dirServer + '/login',
            method: 'PUT',
            headers: {'Content-Type': 'application/json'},
            data: {nombre: nombre, pass: pass}

        }).then(
                function (response) {

                    //var data = response.data;
                    console.log(response);
                    console.log(response.status);

                    if (response.status == 200) {
                        $location.path("/interfaz");
                    }
                },
                function (error) {

                    manajerError(error.status, $location);

                }
        );
    }

    $scope.prueba = function () {
        $http.defaults.withCredentials = false;
        $http({
            url: dirServer + "/lights",
            method: 'GET',
        }).then(function (response) {
            status = response.status;
            console.log(response);
            console.log(status);
            if (status == 200) {
                console.log(response.data);
            } else {
                console.log("invalidos");

            }

        });

    }

    function manajerError(pError, $location) {
        if (pError == 500) {
            alert("Login o contraseña incorrectos, por favor ingrese los datos de nuevo");
            $location.path('/login');
        } else {
            //$location.path('/notFound');
        }

    }

});
