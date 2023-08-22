@extends('layout.app')

@section("title", "Home")
@section("warnahome", "active")
@section('judul')
    <i class="fa fa-home"></i> HOME
@endsection

@section('content')
    <div class="container">
        @livewire('live-time')
    </div>
@endsection