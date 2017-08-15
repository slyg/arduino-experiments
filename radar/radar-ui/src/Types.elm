module Types exposing (..)

import Dict exposing (Dict)


type alias Angle =
    Float


type alias Distance =
    Float


type alias Point =
    ( Int, Int )


type alias TrigoPoint =
    { angle : Angle, distance : Distance }


type alias Model =
    { points : Dict Angle Point
    }


type Msg
    = Noop
    | Frame String
