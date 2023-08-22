<?php

namespace App\Http\Controllers;

use App\Models\dataM;
use App\Models\logsM;
use Illuminate\Http\Request;

class iotC extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function data(Request $request)
    {
        try {
            $jsonData = $request->getContent();
            $json = json_decode($jsonData, true);

            $suhu = $json["suhu"];
            $kelembaban = $json["kelembaban"];
            $tegangan = $json["tegangan"];
            $tanggal = date("Y-m-d",$json["waktu"]);
            $jam = date("H:i",$json["waktu"]);


            $data = dataM::first();
            $data->update([
                "suhu" => $suhu,
                "kelembaban" => $kelembaban,
                "tegangan" => $tegangan,
                "tanggal" => $tanggal,
                "jam" => $jam,
            ]);


            $cek = logsM::count();
            if($cek > 0) {
                $ambil = logsM::orderBy("idlogs", "desc")->first();
                $terakhir = strtotime(date("Y-m-d H:i", strtotime($ambil->tanggal." ".$ambil->jam))); 
                $menit = strtotime("+1 minutes", $terakhir); 
                $kirim = strtotime(date("Y-m-d H:i", $json["waktu"])); 

                if($kirim > $menit) {
                    $tambah = new logsM([
                        "suhu" => $suhu,
                        "kelembaban" => $kelembaban,
                        "tegangan" => $tegangan,
                        "tanggal" => $tanggal,
                        "jam" => $jam,
                    ]);
                    $tambah->save();
                }

            }else {
                $tambah = new logsM([
                    "suhu" => $suhu,
                    "kelembaban" => $kelembaban,
                    "tegangan" => $tegangan,
                    "tanggal" => $tanggal,
                    "jam" => $jam,
                ]);
                $tambah->save();
            }
            $pesan = [
                "pesan" => "Data berhasil diupdate",
            ];
            return $pesan;
        } catch (\Throwable $th) {
            $pesan = [
                "pesan" => "Gagal mengirim data",
            ];
            return $pesan;
        }   
        


    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        //
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        //
    }

    /**
     * Display the specified resource.
     *
     * @param  \App\Models\dataM  $dataM
     * @return \Illuminate\Http\Response
     */
    public function show(dataM $dataM)
    {
        //
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  \App\Models\dataM  $dataM
     * @return \Illuminate\Http\Response
     */
    public function edit(dataM $dataM)
    {
        //
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \App\Models\dataM  $dataM
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, dataM $dataM)
    {
        //
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  \App\Models\dataM  $dataM
     * @return \Illuminate\Http\Response
     */
    public function destroy(dataM $dataM)
    {
        //
    }
}
