module Main exposing (..)

import Html exposing (Html, div, program)
import Html.Attributes exposing (style)
import Types exposing (..)
import Dict exposing (Dict)
import List
import Svg exposing (svg, circle)
import Svg.Attributes exposing (cx, cy, r, width, height, fill, viewBox)
import WebSocket exposing (listen)
import Json.Decode as Decode exposing (Decoder, field, float, decodeString)


init =
    ( Model Dict.empty, Cmd.none )


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        Noop ->
            model ! []

        Frame msg ->
            let
                trigoPoint =
                    msg
                        |> decodeString trigoPointDecoder
                        |> Result.withDefault { angle = 0, distance = 0 }

                angle =
                    trigoPoint.angle

                point =
                    trigoToCartesianPoint trigoPoint

                _ =
                    Debug.log "trigoPoint" point
            in
                { model | points = Dict.insert angle point model.points } ! []


trigoPointDecoder : Decoder TrigoPoint
trigoPointDecoder =
    Decode.map2 TrigoPoint
        (field "angle" float)
        (field "distance" float)


trigoToCartesianPoint : TrigoPoint -> Point
trigoToCartesianPoint { distance, angle } =
    let
        zoom =
            (*) 5

        x =
            distance
                |> (*) (cos (degrees angle))
                |> floor
                |> zoom

        y =
            distance
                |> (*) (sin (degrees (angle + 180)))
                |> floor
                |> zoom
    in
        ( x, y )


subscriptions : Model -> Sub Msg
subscriptions model =
    listen "ws://localhost:9999" Frame


viewPoint : Point -> Html Msg
viewPoint ( x, y ) =
    circle
        [ cx (toString (250 + x))
        , cy (toString (250 + y))
        , r "5"
        , fill "#aacc66"
        ]
        []


view : Model -> Html Msg
view model =
    let
        layout =
            circle
                [ cx "250"
                , cy "250"
                , r "250"
                , fill "#efefef"
                ]
                []

        circles =
            model.points
                |> Dict.values
                |> List.map viewPoint
    in
        div
            [ style
                [ ( "width", "500px" )
                , ( "display", "block" )
                , ( "margin", "50px auto" )
                ]
            ]
            [ svg [ width "500", height "250", viewBox "0 0 500 250" ]
                (layout :: circles)
            ]


main =
    program
        { init = init
        , view = view
        , update = update
        , subscriptions = subscriptions
        }
