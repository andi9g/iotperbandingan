<?php

namespace App\Http\Livewire;

use Livewire\Component;
use App\Models\dataM;

class LiveTime extends Component
{
    public $suhu, $kelembaban, $tegangan, $tangal;


    public function render()
    {
        $data = dataM::first();
        $this->suhu = $data->suhu;
        $this->kelembaban = $data->kelembaban;
        $this->tegangan = $data->tegangan;
        $this->tanggal = \Carbon\Carbon::parse($data->tanggal)->isoFormat("dddd, DD MMMM Y").", ".$data->jam;
        return view('livewire.live-time');
    }

    public function reload() {
        $data = dataM::first();
        $this->suhu = $data->suhu;
        $this->kelembaban = $data->kelembaban;
        $this->tegangan = $data->tegangan;
        $this->tanggal = \Carbon\Carbon::parse($data->tanggal)->isoFormat("dddd, DD MMMM Y").", ".$data->jam;
    }


}
