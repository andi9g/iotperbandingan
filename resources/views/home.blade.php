@extends('layout.app')

@section("title", "Home")
@section("warnahome", "active")
@section('judul')
    <i class="fa fa-home"></i> HOME
@endsection

@section('content')
    <div class="container">
        <div class="row">
            <div class="col-md-6 px-4">
                <div class="card">
                    <div class="card-header card-outline card-primary">
                        <center>
                            <h3 class="my-0">
                                <b>
                                    NodeMCU ESP 8266
                                </b>
                            </h3>
                        </center>
                    </div>
                </div>
                @livewire('live-time')
            </div>

            <div class="col-md-6 px-4">
                <div class="card">
                    <div class="card-header card-outline card-primary">
                        <center>
                            <h3 class="my-0">
                                <b>
                                    WEMOS D1 R2
                                </b>
                            </h3>
                        </center>
                    </div>
                </div>
                @livewire('live-time2')
            </div>
        </div>
    </div>
@endsection