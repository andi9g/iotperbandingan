<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\dataM;
use App\Models\logsM;
use App\Models\logs2M;

class homeC extends Controller
{
    public function index(Request $request)
    {
        return view("home");
    }

    public function logs(Request $request)
    {
        $logs = logsM::orderBy("idlogs", "desc")->paginate(15);

        $logs->appends($request->all());
        $logs2 = logs2M::orderBy("idlogs", "desc")->paginate(15);

        $logs2->appends($request->all());

        return view("logs", [
            "data" => $logs,
            "data2" => $logs2,
        ]);
    }
}
