module Types exposing (..)

import Dict exposing (Dict)


type alias Angle =
    Int


type alias Point =
    ( Int, Int )


type alias Model =
    { points : Dict Angle Point
    }


type Msg
    = Noop
