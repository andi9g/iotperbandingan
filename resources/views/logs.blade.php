@extends('layout.app')

@section("title", "Histori")
@section("warnalogs", "active")
@section('judul')
    <i class="fa fa-database"></i> HISTORI
@endsection

@section('content')
    <div class="container">
        <div class="row">
            <div class="col-md-6">
                <div class="card">
                    <div class="card-header">
                        <h5 class="my-0">
                            <b>
                                NodeMCU ESP8266
                            </b>
                        </h5>
                    </div>
                    <div class="card-body">
                        <table class="table table-sm table-hover table-striped table-bordered">
                            <thead>
                                <th>No</th>
                                <th>Tanggal</th>
                                <th>Suhu</th>
                                <th>Tegangan</th>
                            </thead>
        
                            <tbody>
                                @foreach ($data as $item)
                                    <tr>
                                        <td>{{ $loop->iteration + $data->firstItem() - 1 }}</td>
                                        <td>{{ \Carbon\Carbon::parse($item->tanggal)->isoFormat("DD MMMM Y").", ".$item->jam }}</td>
                                        <td>{{ $item->suhu }}</td>
                                        <td>{{ $item->tegangan }}</td>
                                    </tr>
                                @endforeach
                            </tbody>
                        </table>
                    </div>
                    <div class="card-footer">
                        {{ $data2->links("vendor.pagination.bootstrap-4") }}
                    </div>
                </div>
            </div>

            <div class="col-md-6">
                <div class="card">
                    <div class="card-header">
                        <h5 class="my-0">
                            <b>
                                HISTORI WEMOS D1 R2
                            </b>
                        </h5>
                    </div>
                    <div class="card-body">
                        <table class="table table-sm table-hover table-striped table-bordered">
                            <thead>
                                <th>No</th>
                                <th>Tanggal</th>
                                <th>Suhu</th>
                                <th>Tegangan</th>
                            </thead>
        
                            <tbody>
                                @foreach ($data2 as $item)
                                    <tr>
                                        <td>{{ $loop->iteration + $data2->firstItem() - 1 }}</td>
                                        <td>{{ \Carbon\Carbon::parse($item->tanggal)->isoFormat("DD MMMM Y").", ".$item->jam }}</td>
                                        <td>{{ $item->suhu }}</td>
                                        <td>{{ $item->tegangan }}</td>
                                    </tr>
                                @endforeach
                            </tbody>
                        </table>
                    </div>
                    <div class="card-footer">
                        {{ $data2->links("vendor.pagination.bootstrap-4") }}
                    </div>
                </div>
            </div>
        </div>
    </div>
@endsection