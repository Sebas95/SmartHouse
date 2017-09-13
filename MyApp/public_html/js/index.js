/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

var dirServer = 'http://localhost:10001'

var app = angular.module('myApp', ['ngRoute'])
        .config(['$httpProvider', function ($httpProvider) {
                $httpProvider.defaults.withCredentials = true;
                $httpProvider.defaults.useXDomain = true;
            }]);


app.config(function ($routeProvider) {
    $routeProvider.
            when('/login', {
                templateUrl: 'Pages/login.html',
                controller: 'ctlrLogin'
            }).
            when('/users', {
                templateUrl: 'Pages/users.html',
                controller: 'ctlrRegistrar'
            }).
            when('/interfaz', {
                templateUrl: 'Pages/interfaz.html',
                controller: 'ctlrInterfaz'
            }).
            otherwise({
                redirectTo: '/login'
            });
});


app.factory("InforUser", function () {
    return {
        data: {}
    };
});



