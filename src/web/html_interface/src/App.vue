<script setup lang="ts">
import axios from 'axios';
import { extractInteger } from 'vuetify/lib/components/VTimePicker/util.mjs';


            enum Direction {
                FORWARD = 1,
                REVERSE = 2,
                STOP = 3
            }
            type lampState = 'on' | 'off' | null;
            type singleFrame = 'f' | 'r' | null;

            const messenger = axios.create({
  baseURL: 'http://filmo.local',
  withCredentials: true,

headers: {
    'Content-Type': 'application/json',
    'Access-Control-Allow-Origin': 'http://filmo.local',
    'Access-Control-Allow-Methods': 'GET, POST, PUT, DELETE',
    'Access-Control-Allow-Headers': 'Authorization'
  }
});


            class internaldata {

              
                    public isRunning: boolean;
                    public lampOn: lampState;
                    public dir: Direction = 3;
                    public sf: singleFrame = null;
                    /**
                     * name
                     */
                    public getRunning(): string {
                      return this.isRunning.toString();
                    };
                    public getDir() {
                      return this.dir;
                    }
                    public getLastSf() {
                      return this.sf;
                    }
                    public async setDir(newDir: Direction) {
                      this.dir = newDir;
                      messenger.post('/api/dir', {dir: this.dir});
                      console.log("dir set to: ");
                      console.log(this.getDir());
                    }
                    public async sfDir(newSf: singleFrame)
                    {
                      this.sf = newSf;
                      const response = await messenger.post('/api/sf', {sf: this.sf});
                      console.log("sf set to: ");
                      console.log(this.getLastSf());
                    }

                    public async setLamp(newLamp: lampState)
                    {
                      this.lampOn = newLamp;
                      const response = await messenger.post('/api/lamp', {lamp: this.lampOn});
                      console.log("lamp set to: ");
                      console.log(this.lampOn);
                    }
                    constructor(isRunning: boolean, lampOn: lampState, dir: Direction, sf: singleFrame) {};
            }




</script>


<template>
    <v-container>
<v-row size="1">
    <v-card class="py-10" elevation="0" align="center" style="width: 100%; height: 100%">
      <div class="headline">Filmo Controller</div>
    </v-card>
  </v-row>
  <v-row size="2" class="py-1 px-10 justify-center">
    <v-img
    align="center"
    :max-height="75"
    :max-width="75"
  aspect-ratio="4/3"
  cover
  src="./assets/IMG_4144.JPG.jpeg"
></v-img>
  </v-row>
  </v-container>
  <v-container>
  <VCard elevation="0" class="py-15">
      <VDivider
      class="border-opacity-100"
        :thickness="3"
        variant="dotted"
        
      ></VDivider>
  </VCard>
  </v-container>
  <v-container >
    <v-card class="py-20" elevation="0">
    <v-sheet align="center" class="controlpad">
      <v-btn @click="internaldata.prototype.setDir(Direction.REVERSE)" size="x-large" class="py-15" elevation="1" :ripple="true"> << </v-btn>
      <v-btn @click="internaldata.prototype.sfDir('r')" size="x-large" class="py-15" elevation="1" :ripple="true"> < </v-btn>
      <v-btn @click="internaldata.prototype.setDir(Direction.STOP)" size="x-large" class="py-15" elevation="1" :ripple="true"> X </v-btn>
      <v-btn @click="internaldata.prototype.sfDir('f')" size="x-large" class="py-15" elevation="1" :ripple="true"> > </v-btn>
      <v-btn @click="internaldata.prototype.setDir(Direction.FORWARD)"  size="x-large" class="py-15" elevation="1" :ripple="true"> >> </v-btn>
</v-sheet>
</v-card>
  </v-container>
   <v-container>
  <VCard elevation="0" class="py-15">
      <VDivider
      class="border-opacity-100"
        :thickness="3"
        variant="dotted"
        
      ></VDivider>
  </VCard>
  </v-container>

  <v-container>
  <VFooter class="v-flex px-10 align-center" elevation="0">
    <div class="teeny">2026 brandon paterno</div>
  </VFooter>
  </v-container>
</template>

<style src="./App.css"></style>
