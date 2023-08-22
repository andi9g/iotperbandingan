@extends('layout.app')

@section("title", "Histori")
@section("warnalogs", "active")
@section('judul')
    <i class="fa fa-database"></i> HISTORI
@endsection

@section('content')
    <div class="container">
        <div class="card">
            <div class="card-body">
                <h5 class="card-title">Log Histori</h5>
                <table class="table table-sm table-hover table-striped table-bordered">
                    <thead>
                        <th>No</th>
                        <th>Tanggal</th>
                        <th>Suhu</th>
                        <th>Kelembaban</th>
                        <th>Tegangan</th>
                    </thead>

                    <tbody>
                        @foreach ($data as $item)
                            <tr>
                                <td>{{ $loop->iteration + $data->firstItem() - 1 }}</td>
                                <td>{{ \Carbon\Carbon::parse($item->tanggal)->isoFormat("DD MMMM Y").", ".$item->jam }}</td>
                                <td>{{ $item->suhu }}</td>
                                <td>{{ $item->kelembaban }}</td>
                                <td>{{ $item->tegangan }}</td>
                            </tr>
                        @endforeach
                    </tbody>
                </table>
            </div>
        </div>
    </div>
@endsection