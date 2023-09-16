<?php

namespace App\Http\Livewire;

use Livewire\Component;
use App\Models\data2M;

class LiveTime2 extends Component
{
    public $suhu, $kelembaban, $tegangan, $tangal;

    public function render()
    {
        $data = data2M::first();
        $this->suhu = $data->suhu;
        $this->kelembaban = $data->kelembaban;
        $this->tegangan = $data->tegangan;
        $this->tanggal = \Carbon\Carbon::parse($data->tanggal)->isoFormat("dddd, DD MMMM Y").", ".$data->jam;

        return view('livewire.live-time2');
    }


    public function reload() {
        $data = data2M::first();
        $this->suhu = $data->suhu;
        $this->kelembaban = $data->kelembaban;
        $this->tegangan = $data->tegangan;
        $this->tanggal = \Carbon\Carbon::parse($data->tanggal)->isoFormat("dddd, DD MMMM Y").", ".$data->jam;
    }
}
