//I am all ready to make a server.
//Now to do this on top of Node.js and ReasonML, the first thing I'm going to do is install the server package(Serbet).

open Serbet.Endpoint;

//The server package needs to install decco and bs-let
//The reason for these two things aren't just included with the package itself, 
//it's because it's intended that the consumer of the server will use these packages in their own files as well.

open Async; //to give a promise function to (OkString)

module HelloEndpoint ={

    [@decco.decode] //this will generate a function called params_decode that I'll use later.
    //Decco(Decoder) is a language extension that automatically generates encoders and decoders for us.
    type params ={
        name:String
    };

    let endpoint= Serbet.endpoint({
        verb: GET,
        path:"/hello/:name", //name as a parameter
        handler: req => { //req handle the Express request and it should return a (promise) of a response type
        let%Async params =req.requireParams
        //let%Async get the params off of the path!
        (params_decode);//decoder for the params
        //now let's construct our response 
        OkString("Hello there, " ++params.name)//OkString ->we will respond OK 200 with a string,
        -> async;
        //So why we use promises?
        //It's because we use promises as the vehicle to be able to validate params
        // and if there's a problem with them, then we respond to the user
        },
    });
};

let app = Serbet.application(
 
   [ HelloEndpoint.endpoint]
);

