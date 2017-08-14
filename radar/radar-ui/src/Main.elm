module Main exposing (..)

import Html exposing (Html, div, program)
import Html.Attributes exposing (style)
import Types exposing (..)
import Dict exposing (Dict)
import Svg exposing (svg, circle)
import Svg.Attributes exposing (cx, cy, r, width, height, fill, viewBox)


init =
    ( Model Dict.empty, Cmd.none )


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        Noop ->
            init


subscriptions : Model -> Sub Msg
subscriptions model =
    Sub.none


view : Model -> Html Msg
view model =
    div
        [ style
            [ ( "width", "500px" )
            , ( "display", "block" )
            , ( "margin", "50px auto" )
            ]
        ]
        [ svg [ width "500", height "250", viewBox "0 0 500 250" ]
            [ circle
                [ cx "250"
                , cy "250"
                , r "250"
                , fill "#efefef"
                ]
                []
            ]
        ]


main =
    program
        { init = init
        , view = view
        , update = update
        , subscriptions = subscriptions
        }
