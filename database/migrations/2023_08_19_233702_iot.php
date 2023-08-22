<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Hash;

class Iot extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('data', function (Blueprint $table) {
            $table->bigIncrements('iddata');
            $table->string("suhu");
            $table->string("tegangan");
            $table->string("kelembaban");
            $table->date("tanggal");
            $table->char("jam", 5);
            $table->timestamps();
        });

        DB::table("data")->insert([
            "suhu"=> "0C",
            "tegangan"=> "0v",
            "kelembaban"=> "0F",
            "tanggal"=> "1999-01-22",
            "jam"=> "22:22",
        ]);

        Schema::create('logs', function (Blueprint $table) {
            $table->bigIncrements('idlogs');
            $table->string("suhu");
            $table->string("tegangan");
            $table->string("kelembaban");
            $table->date("tanggal");
            $table->char("jam", 5);
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        //
    }
}
