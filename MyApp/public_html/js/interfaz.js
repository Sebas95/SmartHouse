

app.controller("ctlrInterfaz", function ($scope, $http, $location) {
    $http.defaults.withCredentials = false;
    /**
     * Funcion una para el bombillo de la sala
     * @returns {undefined}
     */
    $scope.accion1 = function () {
        if (document.getElementById('boton1').className == 'btn btn-primary btn-block btn-flat') {
            document.getElementById('boton1').className = 'btn btn-danger';
            enviar("bombillo", 1, 1, $location);
        } else {
            document.getElementById('boton1').className = 'btn btn-primary btn-block btn-flat';
            enviar("bombillo", 1, 0, $location);
        }

    }

    /**
     * Funcion una para el bombillo del comedor
     * @returns {undefined}
     */
    $scope.accion2 = function () {
        if (document.getElementById('boton2').className == 'btn btn-primary btn-block btn-flat') {
            document.getElementById('boton2').className = 'btn btn-danger';
            enviar("bombillo", 2, 1, $location);
        } else {
            document.getElementById('boton2').className = 'btn btn-primary btn-block btn-flat';
            enviar("bombillo", 2, 0, $location);
        }
    }

    /**
     * Funcion una para el bombillo del cuarto 2 el cual es el secundario
     * @returns {undefined}
     */
    $scope.accion3 = function () {
        if (document.getElementById('boton3').className == 'btn btn-primary btn-block btn-flat') {
            document.getElementById('boton3').className = 'btn btn-danger';
            enviar("bombillo", 3, 1, $location);
        } else {
            document.getElementById('boton3').className = 'btn btn-primary btn-block btn-flat';
            enviar("bombillo", 3, 0, $location);
        }
    }

    /**
     * Funcion una para el bombillo del cuarto 1 que es el principal
     * @returns {undefined}
     */
    $scope.accion4 = function () {
        if (document.getElementById('boton4').className == 'btn btn-primary btn-block btn-flat') {
            document.getElementById('boton4').className = 'btn btn-danger';
            enviar("bombillo", 4, 1, $location);
        } else {
            document.getElementById('boton4').className = 'btn btn-primary btn-block btn-flat';
            enviar("bombillo", 4, 0, $location);
        }
    }

    /**
     * Funcion una para el bombillo de la cocina
     * @returns {undefined}
     */
    $scope.accion5 = function () {
        if (document.getElementById('boton5').className == 'btn btn-primary btn-block btn-flat') {
            document.getElementById('boton5').className = 'btn btn-danger';
            enviar("bombillo", 5, 1, $location);
        } else {
            document.getElementById('boton5').className = 'btn btn-primary btn-block btn-flat';
            enviar("bombillo", 5, 0, $location);
        }
    }

    /**
     * Funcion una para la puerta principal
     * @returns {undefined}
     */
    $scope.principal = function () {
        if (document.getElementById('principal').className == 'btn btn-success btn-block btn-flat') {
            document.getElementById('principal').className = 'btn btn-warning';
            enviar("puerta", 1, 1, $location);
        } else {
            document.getElementById('principal').className = 'btn btn-success btn-block btn-flat';
            enviar("puerta", 1, 0, $location);
        }
    }

    /**
     * Funcion una para la puerta del cuarto 1 que es el principal
     * @returns {undefined}
     */
    $scope.cuarto1 = function () {
        if (document.getElementById('cuarto1').className == 'btn btn-success btn-block btn-flat') {
            document.getElementById('cuarto1').className = 'btn btn-warning';
            enviar("puerta", 2, 1, $location);
        } else {
            document.getElementById('cuarto1').className = 'btn btn-success btn-block btn-flat';
            enviar("puerta", 2, 0, $location);
        }
    }

    /**
     * Funcion una para la puerta cuarto 2 que es el secundario
     * @returns {undefined}
     */
    $scope.cuarto2 = function () {
        if (document.getElementById('cuarto2').className == 'btn btn-success btn-block btn-flat') {
            document.getElementById('cuarto2').className = 'btn btn-warning';
            enviar("puerta", 3, 1, $location);
        } else {
            document.getElementById('cuarto2').className = 'btn btn-success btn-block btn-flat';
            enviar("puerta", 3, 0, $location);
        }
    }

    /**
     * Funcion una para la puerta tracera de la casa
     * @returns {undefined}
     */
    $scope.tracera = function () {
        if (document.getElementById('tracera').className == 'btn btn-success btn-block btn-flat') {
            document.getElementById('tracera').className = 'btn btn-warning';
            enviar("puerta", 4, 1, $location);
        } else {
            document.getElementById('tracera').className = 'btn btn-success btn-block btn-flat';
            enviar("puerta", 4, 0, $location);
        }
    }

    /**
     * Funcion una para la activar o desactivar todos los bombillos
     * @returns {undefined}
     */
    $scope.bombillos = function () {
        if (document.getElementById('bombillos').className == 'btn btn-info btn-block btn-flat') {
            document.getElementById('bombillos').className = 'btn btn btn-danger';
        } else {
            document.getElementById('bombillos').className = 'btn btn-info btn-block btn-flat';
        }
        allBombillos();
    }

    /**
     * Funcion una para la activar o desactivar todos las puertas
     * @returns {undefined}
     */
    $scope.puertas = function () {
        if (document.getElementById('puertas').className == 'btn btn-info btn-block btn-flat') {
            document.getElementById('puertas').className = 'btn btn-warning';
        } else {
            document.getElementById('puertas').className = 'btn btn-info btn-block btn-flat';
        }
        allPuertas();
    }

    /**
     * Funcion una para cambiar a los bombillos
     * @returns {undefined}
     */
    allBombillos = function () {
        if (document.getElementById('boton1').className == 'btn btn-primary btn-block btn-flat') {
            document.getElementById('boton1').className = 'btn btn-danger';
        } else {
            document.getElementById('boton1').className = 'btn btn-primary btn-block btn-flat';
        }

        if (document.getElementById('boton2').className == 'btn btn-primary btn-block btn-flat') {
            document.getElementById('boton2').className = 'btn btn-danger';
        } else {
            document.getElementById('boton2').className = 'btn btn-primary btn-block btn-flat';
        }

        if (document.getElementById('boton3').className == 'btn btn-primary btn-block btn-flat') {
            document.getElementById('boton3').className = 'btn btn-danger';
        } else {
            document.getElementById('boton3').className = 'btn btn-primary btn-block btn-flat';
        }

        if (document.getElementById('boton4').className == 'btn btn-primary btn-block btn-flat') {
            document.getElementById('boton4').className = 'btn btn-danger';
        } else {
            document.getElementById('boton4').className = 'btn btn-primary btn-block btn-flat';
        }

        if (document.getElementById('boton5').className == 'btn btn-primary btn-block btn-flat') {
            document.getElementById('boton5').className = 'btn btn-danger';
        } else {
            document.getElementById('boton5').className = 'btn btn-primary btn-block btn-flat';
        }
    }

    /**
     * Funcion una para cambiar a las puertas
     * @returns {undefined}
     */
    allPuertas = function () {
        if (document.getElementById('principal').className == 'btn btn-success btn-block btn-flat') {
            document.getElementById('principal').className = 'btn btn-warning';
        } else {
            document.getElementById('principal').className = 'btn btn-success btn-block btn-flat';
        }

        if (document.getElementById('cuarto1').className == 'btn btn-success btn-block btn-flat') {
            document.getElementById('cuarto1').className = 'btn btn-warning';
        } else {
            document.getElementById('cuarto1').className = 'btn btn-success btn-block btn-flat';
        }

        if (document.getElementById('cuarto2').className == 'btn btn-success btn-block btn-flat') {
            document.getElementById('cuarto2').className = 'btn btn-warning';
        } else {
            document.getElementById('cuarto2').className = 'btn btn-success btn-block btn-flat';
        }

        if (document.getElementById('tracera').className == 'btn btn-success btn-block btn-flat') {
            document.getElementById('tracera').className = 'btn btn-warning';
        } else {
            document.getElementById('tracera').className = 'btn btn-success btn-block btn-flat';
        }
    }


    function enviar(id, num , estado ,$location) {
        $http.defaults.withCredentials = false;
        $http({
            url: dirServer + '/interfaz',
            method: 'PUT',
            headers: {'Content-Type': 'application/json'},
            data: {id: id, numero: num, estado: estado}

        }).then(
                function (response) {

                    //var data = response.data;
                    console.log(response);
                    console.log(response.status);

                    if (response.status == 200) {
                        $location.path("/interfaz");
                    }
                },
                //function (error) {

                   // manajerError(error.status, $location);

                //}
        );
        
    }

});

