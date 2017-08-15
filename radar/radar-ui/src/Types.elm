module Types exposing (..)

import Dict exposing (Dict)


type alias Angle =
    Float


type alias Distance =
    Float


type alias Coord =
    ( Int, Int )


type alias SphericalCoordRecord =
    { angle : Angle, distance : Distance }


type alias SphericalCoord =
    ( Angle, Distance )


type alias Model =
    { points : Dict Angle Coord
    }


type Msg
    = Noop
    | Frame String
