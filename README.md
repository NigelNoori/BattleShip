# ShapeREST
This is an example of a REST application that uses the microservice architecture and Oat++.

![](images/architecture.png "ShapeREST Architecture")

## Compiling
1. Run `make servers`

## Start Servers
1. Run `shapeServer/shapeServer`
1. Run `coneServer/coneServer`
1. Run `circleServer/circleServer`

You could also go into the sub-directories and run the executables.

## Accessing Endpoints
The following URLs will take you to pages that are created by the `ENDPOINT_INFO` sections in the respective `Controller.cpp` files.

These URLs can be used to test your REST endpoints (and that is what we will have you do in the demos)

There are also direct links (using `GET`) for specific queries to the three different servers.

## ShapeServer
### Using SwaggerUI page
1. Go to [http://localhost:8000/swagger/ui](http://localhost:8000/swagger/ui)
1. Click on the `GET` button for the `/circle/area/{radius}` REST endpoint.
1. Click `Try it out` (button on the right side).
1. Enter a number into the `radius` textbox.
1. Click `Execute`
1. See what the server response is:
   1. `200: OK` shows the JSON response with the computed area.
   1. `500 Server Error` means the `circleServer` is not running.
1. Continue exploring the other REST endpoints.

### Direct Queries
#### Circle Area (using ShapeServer)
1. Go to [http://localhost:8000/circle/area/3](http://localhost:8000/circle/area/3)
1. See the direct JSON response for the area of circle with a radius of 3.
#### Circle Perimeter (using ShapeServer)
1. Go to [http://localhost:8000/circle/perimeter/4](http://localhost:8000/circle/perimeter/4)
1. See the direct JSON response for the perimeter of circle with a radius of 4.
#### Cone Area (using ShapeServer)
1. Go to [http://localhost:8000/cone/area/2/3](http://localhost:8000/cone/area/2/3)
1. See the direct JSON response for the area of cone with a radius of 2 and height of 3.
#### Cone Volume (using ShapeServer)
1. Go to [http://localhost:8000/cone/volume/2/3](http://localhost:8000/cone/volume/2/3)
1. See the direct JSON response for the volume of cone with a radius of 2 and height of 3.

## Circle Service
### Using SwaggerUI page
1. Go to [http://localhost:8001/swagger/ui](http://localhost:8001/swagger/ui)
1. Click on the `GET` button for the `/circle` REST endpoint.
1. Click `Try it out` (button on the right side).
1. Enter a number into the `radius` textbox.
1. Click `Execute`
1. See what the server response is:
   1. `200: OK` shows the JSON response with the computed area.
   1. `500 Server Error` means the circleServer is not running.
1. Change the `equation` dropdown to `perimeter`
1. Click `Execute`
1. See what the server response is.
1. Click on the POST button for the `/circle` REST endpoint.
1. Click `Try it out` (button on the right side).
1. Change the number for `radius` value in the JSON message.
1. Click `Execute`
1. See what the server response is.
1. Change the `equation` value to `perimeter` in the JSON message.
1. Click `Execute`
1. See what the server response is.

### Direct Queries
#### Circle Area (GET only)
1. Go to [http://localhost:8001/circle?equation=area&radius=3](http://localhost:8001/circle?equation=area&radius=3)
1. See the direct JSON response for the area of circle with a radius of 3.
#### Circle Perimeter (GET only)
1. Go to [http://localhost:8001/circle?equation=perimeter&radius=4](http://localhost:8001/circle?equation=perimeter&radius=4)
1. See the direct JSON response for the perimeter of circle with a radius of 4.


## Cone Service
### Using SwaggerUI page
1. Go to [http://localhost:8002/swagger/ui](http://localhost:8002/swagger/ui)
1. Click on the GET button for the `/cone/area` REST endpoint.
1. Click `Try it out` (button on the right side).
1. Enter a number into the `radius` and `height`textboxes.
1. Click `Execute`
1. See what the server response is:
   1. `200: OK` shows the JSON response with the computed area.
   1. `500 Server Error` means the circleServer is not running.
1. Click on the GET button for the `/cone/volume` REST endpoint.
1. Click `Try it out` (button on the right side).
1. Enter a number into the `radius` and `height`textboxes.
1. Click `Execute`
1. See what the server response is.

### Direct Queries
#### Cone Area (GET only)
1. Go to [http://localhost:8002/cone/area?radius=1&height=2](http://localhost:8002/cone/area?radius=1&height=2)
1. See the direct JSON response for the area of cone with a radius of 1 and height of 2.
#### Cone Volume (GET only)
1. Go to [http://localhost:8002/cone/volume?radius=3&height=4](http://localhost:8002/cone/volume?radius=3&height=4)
1. See the direct JSON response for the volume of a cone with a radius of 2 and height of 4.
